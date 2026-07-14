

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "R1PlayerState.generated.h"

class UR1AbilitySystemComponent;
class UMyPlayerSet;
/**
 * 
 */
UCLASS()
class R1_API AR1PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AR1PlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	
	UR1AbilitySystemComponent* GetR1AbilitySystemComponent() const;
	UMyPlayerSet* GetR1PlayerSet() const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UR1AbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UMyPlayerSet> PlayerSet;

};
