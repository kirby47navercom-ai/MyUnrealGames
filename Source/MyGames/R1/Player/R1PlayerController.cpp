// Fill out your copyright notice in the Description page of Project Settings.


#include "R1PlayerController.h"
#include <memory>

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

void AR1PlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (auto *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(InputMappingContext,0);
}

void AR1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(TestAction,ETriggerEvent::Triggered,this,&ThisClass::InputTest);
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ThisClass::InputMove);
		EnhancedInputComponent->BindAction(TurnAction,ETriggerEvent::Triggered,this,&ThisClass::InputTurn);
	}
}

void AR1PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaTime = DeltaTime;
}

void AR1PlayerController::InputTest(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(0,1.0f,FColor::Cyan,"Test");
}

void AR1PlayerController::InputMove(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	FRotator Rotation = GetPawn()->GetControlRotation();
	FRotator Walk = {0,Rotation.Yaw,0};
	FVector FowardVector = FRotationMatrix(Walk).GetUnitAxis(EAxis::Y);
	FVector RightVector = FRotationMatrix(Walk).GetUnitAxis(EAxis::X);
	GetPawn()->AddMovementInput(FowardVector,InputValue.Get<FVector2D>().X);
	GetPawn()->AddMovementInput(RightVector,InputValue.Get<FVector2D>().Y);

}


void AR1PlayerController::InputTurn(const FInputActionValue& InputValue)
{
	GetPawn()->AddControllerYawInput(InputValue.Get<FVector2D>().X);
	GetPawn()->AddControllerPitchInput((InputValue.Get<FVector2D>().Y));
}
