// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

protected:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> TestAction;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> TurnAction;
	
private:
	void InputTest(const FInputActionValue& InputValue);
	void InputMove(const FInputActionValue& InputValue);
	void InputTurn(const FInputActionValue& InputValue);
	
};
