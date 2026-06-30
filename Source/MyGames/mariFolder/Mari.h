// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "memory"
#include "Components/TimelineComponent.h"
#include "Mari.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class MYGAMES_API AMari : public ACharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Components")
	USpringArmComponent *SpringArmComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Components")
	UCameraComponent *CameraComponent;
protected:
	UPROPERTY(EditAnywhere,Category = "Input")
	UInputAction *JumpAction;
	UPROPERTY(EditAnywhere,Category = "Input")
	UInputAction *MoveAction;
	UPROPERTY(EditAnywhere,Category = "Input")
	UInputAction *LookAction;
	UPROPERTY(EditAnywhere,Category = "Input")
	UInputAction *MouseLookAction;
protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void MoveStart();
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void MoveEnd();
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "TimelineTurn")
	UCurveFloat *TurnCurve;
	
	FRotator TurnStart;
	FRotator TurnEnd;
	
	UFUNCTION()
	void UpdateTurn(float Alpha);
	UFUNCTION()
	void FinishTurn();

	FTimeline TurnTimeline;
	
	void StartTurnTo(const FVector &Direction);
	FVector LastTurnDir = FVector::ZeroVector;
	FVector TurnDirection;
	float TurnTime=0.f;
private:
	UPROPERTY(EditAnywhere,Category = "Input")
	FVector2D JumpGravityScale{1.0f,2.5f};
	void DoJump(const FVector2D &jumpGravityScale);
	
	
public:
	// Sets default values for this character's properties
	AMari();

protected:
	// Called when the game starts or when spawned

public:	
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	float deltaTime;

};
