#pragma once
#include <string>
#include <vector>

#include "Rendering/SkeletalMeshLODImporterData.h"

using namespace std;

struct VVertex
{
	int				PointIndex;				// short, padded to int
	float			U, V;
	char			MatIndex;
	char			Reserved;
	short			Pad;

	SkeletalMeshImportData::FVertex ConvertFVertex(TArray<FColor> VtxColPerVtx)
	{
		SkeletalMeshImportData::FVertex Wedge;
		Wedge.Color = VtxColPerVtx.Num() > 0 ? VtxColPerVtx[PointIndex] : FColor(0,0,0,0);
		Wedge.VertexIndex = PointIndex;
		Wedge.MatIndex = MatIndex;
		Wedge.UVs[0] = FVector2D(U, V);
		return Wedge;
	}
};

struct VTriangle16
{
	int			WedgeIndex[3];			// Point to three vertices in the vertex list.
	char			MatIndex;				// Materials can be anything.
	char			AuxMatIndex;			// Second material (unused).
	unsigned		SmoothingGroups;		// 32-bit flag for smoothing groups.

	SkeletalMeshImportData::FTriangle ConvertFTriangle()
	{
		SkeletalMeshImportData::FTriangle Triangle = SkeletalMeshImportData::FTriangle();
		Triangle.MatIndex = MatIndex;
		Triangle.SmoothingGroups = SmoothingGroups;
		Triangle.WedgeIndex[0] = WedgeIndex[0];
		Triangle.WedgeIndex[1] = WedgeIndex[1];
		Triangle.WedgeIndex[2] = WedgeIndex[2];
		Triangle.AuxMatIndex = AuxMatIndex;
		return Triangle;
	}
};

struct VMaterial
{
	char			MaterialName[64];
	int				TextureIndex;
	unsigned		PolyFlags;
	int				AuxMaterial;
	unsigned		AuxFlags;
	int				LodBias;
	int				LodStyle;
};

struct VJointPos
{
	FQuat			Orientation;
	FVector			Position;
	float			Length;
	FVector			Size;
};

struct VBone
{
	char			Name[64];
	unsigned		Flags;
	int				NumChildren;
	int				ParentIndex;			
	VJointPos*		BonePos;

	SkeletalMeshImportData::FBone ConvertFBone()
	{
		SkeletalMeshImportData::FBone SkelBone = SkeletalMeshImportData::FBone();
		SkelBone.Name = Name;
		SkelBone.Flags = Flags;
		SkelBone.NumChildren = NumChildren;
		SkelBone.ParentIndex = ParentIndex;

		SkeletalMeshImportData::FJointPos JointPos = SkeletalMeshImportData::FJointPos();
		FTransform Transform = FTransform();
		Transform.SetRotation(BonePos->Orientation);
		Transform.SetLocation(FVector(BonePos->Position.X*0.01, BonePos->Position.Y*0.01, BonePos->Position.Z*0.01));
		JointPos.Transform = Transform;
		SkelBone.BonePos = JointPos;

		return SkelBone;
	}
};



struct VRawBoneInfluence
{
	float			Weight;
	int				PointIndex;
	int				BoneIndex;

	SkeletalMeshImportData::FRawBoneInfluence ConvertFRawBoneInfluence()
	{
		SkeletalMeshImportData::FRawBoneInfluence Influence = SkeletalMeshImportData::FRawBoneInfluence();
		Influence.Weight = Weight;
		Influence.VertexIndex = PointIndex;
		Influence.BoneIndex = BoneIndex;
		return Influence;
	}
};

struct FUVArray
{
	TArray<FVector2D> Items;
};

struct FPskData
{
	TArray<FVector> Vertices;
	TArray<VVertex*> Wedges;
	TArray<VTriangle16*> Faces;
	TArray<VMaterial*> Materials;
	TArray<FColor> VertexColors;
	TArray<FUVArray> ExtraUVs;
	TArray<VBone*> Bones;
	TArray<VRawBoneInfluence*> Weights;
};

class PskReader
{
	
public:
	static FPskData ReadPsk(string filepath);
	static bool CheckPskHeader();

	static void ReadVertices(int count, FPskData* data);
	static void ReadWedges(int count, FPskData* data);
	static void ReadFaces(int count, FPskData* data);
	static void ReadVertexColors(int count, FPskData* data);
	static void ReadExtraUVs(int count, FPskData* data);
	static void ReadMaterials(int count, FPskData* data);
	static void ReadBones(int count, FPskData* data);
    static void ReadWeights(int count, FPskData* data);
	
};
