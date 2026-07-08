// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "R1AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYGAMES_API UR1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UR1AnimInstance(const FObjectInitializer& Parent = FObjectInitializer::Get());
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<class AR1Player> Character;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FVector Velocity;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float GroundSpeed;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bShouldMove;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bIsFalling;
	
	
};
