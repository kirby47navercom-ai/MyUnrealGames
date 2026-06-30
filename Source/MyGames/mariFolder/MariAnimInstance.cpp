// Fill out your copyright notice in the Description page of Project Settings.


#include "MariAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

void UMariAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwnerPawn = TryGetPawnOwner();
}

void UMariAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!OwnerPawn)
	OwnerPawn = TryGetPawnOwner();
	if (!OwnerPawn)
	{
		Speed = 0.f;
		bIsFalling = false;
		return;
	}
	FVector Velocity = OwnerPawn->GetVelocity();
	Velocity.Z = 0.0f;
	Speed = Velocity.Size();
	
	if (ACharacter* Character = Cast<ACharacter>(OwnerPawn)) bIsFalling = Character->GetCharacterMovement()->IsFalling();
		
	
}
