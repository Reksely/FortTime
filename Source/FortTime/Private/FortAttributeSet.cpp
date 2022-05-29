


#include "FortAttributeSet.h"
#include "Net/UnrealNetwork.h"

UFortAttributeSet::UFortAttributeSet()
{
}

void UFortAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifeTimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(UFortAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFortAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
}

void UFortAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFortAttributeSet, Health, OldHealth);
}

void UFortAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFortAttributeSet, Stamina, OldStamina);
}


