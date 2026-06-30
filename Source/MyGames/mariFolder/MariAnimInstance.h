// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <gsl/pointers>

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MariAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYGAMES_API UMariAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadOnly)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling;
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	float MoveInputAmount = 0.f;
private:
	UPROPERTY()
	APawn *OwnerPawn = nullptr;
	
};
