#include "PskReader.h"

#include <fstream>
#include <iomanip>
#include <iostream>

#include "Containers/Array.h"
#include "PskFactory.h"

using namespace std;

ifstream is;

// Util Stuff
template <typename T>
T Read(ifstream& stream = is)
{
	char* rawChars = new char[sizeof(T)];
	stream.read(rawChars, sizeof(T));
	T result;
	memcpy(&result, rawChars, sizeof(T));
	return result;
}
char* ReadStr(int size)
{
	auto* bytes = new char[size];
	is.read(&bytes[0], size);
	return bytes;
}
bool InArray(const string &value, const vector<string> &array)
{
	return std::find(array.begin(), array.end(), value) != array.end();
}

bool PskReader::CheckPskHeader()
{
	auto* headerBytes = ReadStr(20);
	is.ignore(sizeof(int)*3);
	return strcmp(headerBytes, "ACTRHEAD") == 0;
}

vector<string> handlers {"PNTS0000", "VTXW0000", "FACE0000", "VERTEXCO", "EXTRAUVS", "MATT0000", "REFSKELT", "REFSKEL0", "RAWWEIGH", "RAWW0000"};

FPskData PskReader::ReadPsk(string filepath)
{
	cout << setprecision(8);
	auto* data = new FPskData();
	is.open(filepath, ios::binary);
	
	if (!CheckPskHeader()) return *new FPskData();
	while (!is.eof() && is.tellg() > 0 )
	{
		auto hdr = ReadStr(20);
		auto flag = Read<int>();
		auto size = Read<int>();
		auto count = Read<int>();

		string hdrS(hdr);
		hdrS = hdrS.substr(0,8);
		hdr = const_cast<char*>(hdrS.c_str());

		if (InArray(hdr, handlers))
		{
			if (strcmp(hdr, "PNTS0000") == 0) ReadVertices(count, data);
			if (strcmp(hdr, "VTXW0000") == 0) ReadWedges(count, data);
			if (strcmp(hdr, "VTXW3200") == 0) ReadWedges(count, data);
			if (strcmp(hdr, "FACE0000") == 0) ReadFaces(count, data);
			if (strcmp(hdr, "FACE3200") == 0) ReadFaces(count, data);
			if (strcmp(hdr, "VERTEXCO") == 0) ReadVertexColors(count, data);
			if (strcmp(hdr, "EXTRAUVS") == 0) ReadExtraUVs(count, data);
			if (strcmp(hdr, "MATT0000") == 0) ReadMaterials(count, data);
			if (strcmp(hdr, "REFSKELT") == 0) ReadBones(count, data);
			if (strcmp(hdr, "REFSKEL0") == 0) ReadBones(count, data);
			if (strcmp(hdr, "RAWW0000") == 0) ReadWeights(count, data);
			if (strcmp(hdr, "RAWWEIGH") == 0) ReadWeights(count, data);
		}
		else
		{
			is.ignore(size*count);

			//UE_LOG(LogPsk, Warning, TEXT("Invalid Header: %s"), *FString(hdr))
		}
			
	}
	is.close();
	return *data;

}

void PskReader::ReadVertices(int count, FPskData* data)
{
	for (int i = 0; i < count; i++)
	{
		data->Vertices.Add(FVector(Read<float>(),Read<float>(),Read<float>()));
	}
}
void PskReader::ReadWedges(int count, FPskData* data)
{
	for (int i = 0; i < count; i++)
	{
		VVertex* Wedge = new VVertex();
		Wedge->PointIndex = Read<int>();
		Wedge->U = Read<float>();
		Wedge->V = Read<float>();
		Wedge->MatIndex = Read<char>();
		Wedge->Reserved = Read<char>();
		Wedge->MatIndex = Read<short>();
		data->Wedges.Add(Wedge);
	}
}
void PskReader::ReadFaces(int count, FPskData* data)
{
	for (int i = 0; i < count; i++)
	{
		if (data->Wedges.Num() <= 65536)
		{
			VTriangle16* Triangle = new VTriangle16();
			Triangle->WedgeIndex[0] = Read<unsigned short>();
			Triangle->WedgeIndex[1] = Read<unsigned short>();
			Triangle->WedgeIndex[2] = Read<unsigned short>();
			Triangle->MatIndex = Read<char>();
			Triangle->AuxMatIndex = Read<char>();
			Triangle->SmoothingGroups = Read<int>();

			data->Faces.Add(Triangle);
		}
		else
		{
			VTriangle16* Triangle = new VTriangle16();
			Triangle->WedgeIndex[0] = Read<int>();
			Triangle->WedgeIndex[1] = Read<int>();
			Triangle->WedgeIndex[2] = Read<int>();
			Triangle->MatIndex = Read<char>();
			Triangle->AuxMatIndex = Read<char>();
			Triangle->SmoothingGroups = Read<int>();

			data->Faces.Add(Triangle);
		}
	}
}
void PskReader::ReadVertexColors(int count, FPskData* data)
{
	for (int i = 0; i < count; i++)
	{
		data->VertexColors.Add(FColor(Read<char>(),Read<char>(),Read<char>(), Read<char>()));
	}
}
void PskReader::ReadExtraUVs(int count, FPskData* data)
{
	FUVArray extrauvs;
	for (int i = 0; i < count; i++)
	{
		extrauvs.Items.Add(FVector2D(Read<float>(), Read<float>()));
	}

	data->ExtraUVs.Add(extrauvs);
	
}
void PskReader::ReadMaterials(int count, FPskData* data)
{
	for (int i = 0; i < count; i++)
	{
		VMaterial* Material = new VMaterial();
		strcpy_s(Material->MaterialName, ReadStr(64));
		Material->TextureIndex = Read<int>();
		Material->PolyFlags = Read<unsigned>();
		Material->AuxMaterial = Read<int>();
		Material->AuxFlags = Read<unsigned>();
		Material->LodBias = Read<int>();
		Material->LodStyle = Read<int>();
		data->Materials.Add(Material);
	}
}
void PskReader::ReadBones(int count, FPskData* data)
{
	for (int i = 0; i < count; i++)
	{
		VBone* Bone = new VBone();
		strcpy_s(Bone->Name, ReadStr(64));
		Bone->Flags = Read<unsigned>();
		Bone->NumChildren = Read<int>();
		Bone->ParentIndex = Read<int>();

		VJointPos* Pos = new VJointPos();
		Pos->Orientation = FQuat(Read<float>(), Read<float>(), Read<float>(), Read<float>());
		Pos->Position = FVector(Read<float>(), Read<float>(), Read<float>());
		is.ignore(16);
		Bone->BonePos = Pos;

		data->Bones.Add(Bone);
	}
}
void PskReader::ReadWeights(int count, FPskData* data)
{
	for (int i = 0; i < count; i++)
	{
		VRawBoneInfluence* Influence = new VRawBoneInfluence();
		Influence->Weight = Read<float>();
		Influence->PointIndex = Read<int>();
		Influence->BoneIndex = Read<int>();
		data->Weights.Add(Influence);
	}
}



