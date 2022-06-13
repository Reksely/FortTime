

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "FortAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 

/**
 * 
 */
UCLASS()
class FORTTIME_API UFortAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public: 

	UFortAttributeSet();

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifeTimeProps) const override;


	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UFortAttributeSet, Health);

	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UFortAttributeSet, Stamina);

	UFUNCTION()
		virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
	
};
