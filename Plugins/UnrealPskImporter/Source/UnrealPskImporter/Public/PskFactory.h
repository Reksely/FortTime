#pragma once

#include "PskFactory.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPsk, Log, All);

UCLASS()
class UPskFactory : public UFactory
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UStaticMesh* FinalStaticMesh = nullptr;

	UPROPERTY()
	USkeletalMesh* FinalSkeletalMesh = nullptr;

	UPskFactory();
	virtual ~UPskFactory();

	virtual UObject* FactoryCreateFile
    (
        UClass* inClass,
        UObject* inParent,
        FName inName,
        EObjectFlags flags,
        const FString& filename,
        const TCHAR* parms,
        FFeedbackContext* warn,
        bool& bOutOperationCanceled
    ) override;

	virtual bool DoesSupportClass(UClass* Class) override;

	virtual bool FactoryCanImport(const FString& Filename) override;

private:
	void Import(UClass* inClass, UObject* inParent, FName inName, EObjectFlags flags, const FString& path, FString extension, FFeedbackContext* warn);
	
};
