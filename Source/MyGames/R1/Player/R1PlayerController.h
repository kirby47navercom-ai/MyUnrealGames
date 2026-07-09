// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../R1Define.h"
#include "GameplayTagContainer.h"
#include "R1PlayerController.generated.h"

/**
 * 
 */
struct FInputActionValue;

UCLASS()
class MYGAMES_API AR1PlayerController : public APlayerController
{
	GENERATED_BODY()

	
public:
	AR1PlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

public:
	virtual void HandleGameplayEvent(FGameplayTag EventTag);

private:
	void TickCursorTrace();
	void ChaseTargetAndAttack();

	void Input_Move(const FInputActionValue& InputValue);
	void Input_Turn(const FInputActionValue& InputValue);
	void Input_Jump(const FInputActionValue& InputValue);
	void Input_Attack(const FInputActionValue& InputValue);
	void Input_Active_SetDestination(const FInputActionValue& InputValue);
	
	void OnInputStarted();
	void OnSetDestinationTrigger();
	void OnSetDestinationReleased();

	ECreatureState GetCreatureState();
	void SetCreatureState(ECreatureState InState);
	
	
	
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> AttackMontage;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input)
	float ShortPressThreshold = 0.3f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input)
	TObjectPtr<class UNiagaraSystem> FXCursor;
	
private:
	FVector CachedDestination;
	float FollowTime;
	bool bMousePressed = false;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AR1Character> TargetActor;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AR1Character> HighlightActor;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AR1Player> R1Player;
	
	
	
};
