#include "PskFactory.h"

#include <fstream>



#include "AnimationEditorUtils.h"
#include "AssetImportTask.h"
#include "ContentBrowserModule.h"
#include "PskReader.h"
#include "RawMesh.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "EditorFramework/AssetImportData.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Rendering/SkeletalMeshModel.h"
#include "Runtime/Engine/Public/SkeletalMeshMerge.h"

DEFINE_LOG_CATEGORY(LogPsk);

UPskFactory::UPskFactory()
{
	// We only want to create assets by importing files.
	// Set this to true if you want to be able to create new, empty Assets from
	// the editor.
	bCreateNew = false;

	// Our Asset will be imported from a binary file
	bText = false;

	// Allows us to actually use the "Import" button in the Editor for this Asset
	bEditorImport = true;

	// Tells the Editor which file types we can import
	Formats.Add(TEXT("psk;ActorX Skeletal Mesh"));
	Formats.Add(TEXT("pskx;ActorX Static Mesh"));

	// Tells the Editor which Asset type this UFactory can import
	SupportedClass = UStaticMesh::StaticClass();
}

UPskFactory::~UPskFactory()
{
	
}

UObject* UPskFactory::FactoryCreateFile(UClass* inClass, UObject* inParent, FName inName, EObjectFlags flags,
	const FString& filename, const TCHAR* parms, FFeedbackContext* warn, bool& bOutOperationCanceled)
{
	/*UAssetImportTask* task = AssetImportTask;
	if (task == nullptr)
	{
		task = NewObject<UAssetImportTask>();
		task->Filename = filename;
	}

	if (ScriptFactoryCreateFile(task))
	{
		return task->Result[0];
	}

	FString extension = FPaths::GetExtension(filename);
	FString path = FPaths::GetPath(filename);
	GEditor->GetEditorSubsystem<UImportSubsystem>()->BroadcastAssetPreImport(this, inClass, inParent, inName, *extension);

	Import(inClass, inParent, inName, flags, filename, extension, warn);

	if (FinalStaticMesh != nullptr)
	{
		FinalStaticMesh->AssetImportData->Update(CurrentFilename, FileHash.IsValid() ? &FileHash : nullptr);
		GEditor->GetEditorSubsystem<UImportSubsystem>()->BroadcastAssetPostImport(this, FinalStaticMesh);
		FinalStaticMesh->PostEditChange();
	}*/

	FString extension = FPaths::GetExtension(filename);
	FString path = FPaths::GetPath(filename);
	
	Import(inClass, inParent, inName, flags, filename, extension, warn);
	
	return FinalStaticMesh != nullptr ? (UObject*) FinalStaticMesh : (UObject*) FinalSkeletalMesh;
}

bool UPskFactory::DoesSupportClass(UClass* Class)
{
	return Class == UStaticMesh::StaticClass() || Class == USkeletalMesh::StaticClass();
}

bool UPskFactory::FactoryCanImport(const FString& Filename)
{
	FString extension = FPaths::GetExtension(Filename);
	bool isPsk = extension.Compare("psk", ESearchCase::IgnoreCase) == 0;
	bool isPskx = extension.Compare("pskx", ESearchCase::IgnoreCase) == 0;
	return isPsk || isPskx;
}

void UPskFactory::Import(UClass* inClass, UObject* inParent, FName inName, EObjectFlags flags, const FString& path,
	FString extension, FFeedbackContext* warn)
{
	FPskData data = PskReader::ReadPsk(string(TCHAR_TO_UTF8(*path)));

	// VtxColor Vertex Mapping
	TArray<FColor> PerVertex;
	if (data.VertexColors.Num() > 0)
	{
		PerVertex.Init(FColor(0,0,0,0),data.Vertices.Num());
		for (int i = 0; i < data.Wedges.Num(); i++) 
		{
			VVertex* wdg = data.Wedges[i];
			PerVertex[wdg->PointIndex] = data.VertexColors[i];
		}
	}
	
	/*if (extension.Equals("psk")) // SkeletalMesh
	{
		
		USkeletalMesh* SkeletalMesh = CastChecked<USkeletalMesh>(CreateOrOverwriteAsset(USkeletalMesh::StaticClass(), inParent, inName, flags));
		USkeleton* Skeleton = CastChecked<USkeleton>(CreateOrOverwriteAsset(USkeleton::StaticClass(), inParent, inName, flags));
		SkeletalMesh->Skeleton = Skeleton;
		
		FReferenceSkeleton SkeletonSource;
		FReferenceSkeletonModifier SkeletonSourceModifier(SkeletonSource, Skeleton);
		{
			SkeletonSource.Empty(data.Bones.Num());
		
			for (int boneIdx = 0; boneIdx < data.Bones.Num(); boneIdx++)
			{
				VBone* bone = data.Bones[boneIdx];
			
				FMeshBoneInfo BoneInfo = FMeshBoneInfo(FName(bone->Name), FString(bone->Name), boneIdx == 0 ? INDEX_NONE : bone->ParentIndex);

				FTransform BonePose;
				BonePose.SetRotation(bone->BonePos->Orientation.GetNormalized());
				BonePose.SetLocation(bone->BonePos->Position);
				SkeletonSourceModifier.Add(BoneInfo, BonePose);
			}
		}
		SkeletalMesh->RefSkeleton = SkeletonSource;
		//=SkeletalMesh->bHasVertexColors = data.VertexColors.Num() > 0;
		Skeleton->RecreateBoneTree(SkeletalMesh);

		// Mesh Stuff
		FSkeletalMeshImportData ImportData;
		ImportData.Points = data.Vertices;
		ImportData.bHasVertexColors = data.VertexColors.Num() > 0;
		for (VVertex* wdg : data.Wedges) ImportData.Wedges.Add(wdg->ConvertFVertex(PerVertex));
		for (VTriangle16* tri : data.Faces) ImportData.Faces.Add(tri->ConvertFTriangle());
		for (VBone* bone : data.Bones) ImportData.RefBonesBinary.Add(bone->ConvertFBone());
		for (VRawBoneInfluence* inf : data.Weights) ImportData.Influences.Add(inf->ConvertFRawBoneInfluence());
		
		FSkeletalMeshModel* MeshModel = SkeletalMesh->GetImportedModel();
		MeshModel->LODModels.Empty();
		SkeletalMesh->ResetLODInfo();
		
		FSkeletalMeshLODModel* LOD = new FSkeletalMeshLODModel();
		LOD->NumTexCoords = data.ExtraUVs.Num()+1;
		FSkeletalMeshLODInfo& LODInfo = SkeletalMesh->AddLODInfo();
		LODInfo.BuildSettings.bRecomputeNormals = true;
		LODInfo.BuildSettings.bRecomputeTangents = true;
		MeshModel->LODModels.Add(LOD);

		SkeletalMesh->SaveLODImportedData(0, ImportData);
		USkeletalMesh::CalculateRequiredBones(*LOD, SkeletonSource, nullptr);

		SkeletalMesh->CalculateInvRefMatrices();
		SkeletalMesh->Build();

		FAssetRegistryModule::AssetCreated(SkeletalMesh);
		FAssetRegistryModule::AssetCreated(Skeleton);
		
	}*/
	if (extension.Equals("pskx") || extension.Equals("psk")) // StaticMesh
	{
		FRawMesh RawMesh = FRawMesh();
		for (FVector vec : data.Vertices)
		{
			RawMesh.VertexPositions.Add(vec.RotateAngleAxis(-90, FVector(0,1,0)));
		}
		for (VTriangle16* tri : data.Faces)
		{
			VVertex* W0 = data.Wedges[tri->WedgeIndex[0]];
			VVertex* W1 = data.Wedges[tri->WedgeIndex[1]];
			VVertex* W2 = data.Wedges[tri->WedgeIndex[2]];

			RawMesh.WedgeIndices.Add(W1->PointIndex);
			RawMesh.WedgeIndices.Add(W0->PointIndex);
			RawMesh.WedgeIndices.Add(W2->PointIndex);

			RawMesh.WedgeTexCoords->Add(FVector2D(W1->U, W1->V));
			RawMesh.WedgeTexCoords->Add(FVector2D(W0->U, W0->V));
			RawMesh.WedgeTexCoords->Add(FVector2D(W2->U, W2->V));

			for (int i = 0; i < data.ExtraUVs.Num(); i++)
			{
				FVector2D UV0 = data.ExtraUVs[i].Items[tri->WedgeIndex[0]];
				FVector2D UV1 = data.ExtraUVs[i].Items[tri->WedgeIndex[1]];
				FVector2D UV2 = data.ExtraUVs[i].Items[tri->WedgeIndex[2]];
				
				RawMesh.WedgeTexCoords[i+1].Add(UV1);
				RawMesh.WedgeTexCoords[i+1].Add(UV0);
				RawMesh.WedgeTexCoords[i+1].Add(UV2);
			}

			if (data.VertexColors.Num() > 0)
			{
				RawMesh.WedgeColors.Add(PerVertex[W1->PointIndex]);
				RawMesh.WedgeColors.Add(PerVertex[W0->PointIndex]);
				RawMesh.WedgeColors.Add(PerVertex[W2->PointIndex]);
			}

			RawMesh.WedgeTangentX.Add(FVector::ZeroVector);
			RawMesh.WedgeTangentX.Add(FVector::ZeroVector);
			RawMesh.WedgeTangentX.Add(FVector::ZeroVector);

			RawMesh.WedgeTangentY.Add(FVector::ZeroVector);
			RawMesh.WedgeTangentY.Add(FVector::ZeroVector);
			RawMesh.WedgeTangentY.Add(FVector::ZeroVector);

			RawMesh.WedgeTangentZ.Add(FVector::ZeroVector);
			RawMesh.WedgeTangentZ.Add(FVector::ZeroVector);
			RawMesh.WedgeTangentZ.Add(FVector::ZeroVector);

			RawMesh.FaceMaterialIndices.Add(tri->MatIndex);

			RawMesh.FaceSmoothingMasks.Add(1);
		}

		UObject* newObject = CreateOrOverwriteAsset(UStaticMesh::StaticClass(), inParent, inName, flags);
		UStaticMesh* StaticMesh = nullptr;
		if (newObject) StaticMesh = CastChecked<UStaticMesh>(newObject);
		StaticMesh->MarkPackageDirty();
		for (int i = 0; i < data.Materials.Num(); i++)
		{
			FName MaterialBaseName = FName( data.Materials[i]->MaterialName);

			UObject* MatObj = CreateOrOverwriteAsset(UMaterialInstanceConstant::StaticClass(), inParent, MaterialBaseName, flags);
			FAssetRegistryModule::AssetCreated(MatObj);
			MatObj->MarkPackageDirty();

			FStaticMaterial StaticMaterial;
			StaticMaterial.MaterialInterface = CastChecked<UMaterialInstanceConstant>(MatObj);
			StaticMesh->GetStaticMaterials().Add(StaticMaterial);
			StaticMesh->GetSectionInfoMap().Set(0, i, FMeshSectionInfo(i));
		}
	
		//StaticMesh->PreEditChange(nullptr);
		FStaticMeshSourceModel & SourceModel = StaticMesh->AddSourceModel();
		SourceModel.BuildSettings.bGenerateLightmapUVs = false;
		SourceModel.BuildSettings.bBuildAdjacencyBuffer = false;
		SourceModel.BuildSettings.bBuildReversedIndexBuffer = false;
		SourceModel.BuildSettings.bRecomputeNormals = true;
		SourceModel.BuildSettings.bRecomputeTangents = true;
		SourceModel.SaveRawMesh(RawMesh);

		StaticMesh->Build();
		FAssetRegistryModule::AssetCreated(StaticMesh);
		FinalStaticMesh = StaticMesh;
	}
}



