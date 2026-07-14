

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/R1GameplayAbility.h"
#include "R1GameplayAbility_Attack.generated.h"

/**
 * 
 */
UCLASS()
class R1_API UR1GameplayAbility_Attack : public UR1GameplayAbility
{
	GENERATED_BODY()
public:
	UR1GameplayAbility_Attack(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* SourceTags,const FGameplayTagContainer* TargetTags,FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* SourceTags,const FGameplayEventData* TriggerEventData)override;
	virtual void EndAbility()override;
};
