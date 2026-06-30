// Fill out your copyright notice in the Description page of Project Settings.


#include "Mari.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include  "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "SNegativeActionButton.h"
#include "Chaos/SoftsSpring.h"
#include "Components/CapsuleComponent.h"


void AMari::Move(const FInputActionValue& Value)
{
	
	DoMove(Value.Get<FVector2D>().X,Value.Get<FVector2D>().Y);
	
}

void AMari::BeginPlay()
{
	Super::BeginPlay();
	
	if (TurnCurve)
	{
		FOnTimelineFloat Update;
		Update.BindUFunction(this,FName("UpdateTurn"));
		FOnTimelineEvent Finish;
		Finish.BindUFunction(this,FName("FinishTurn"));
		
		TurnTimeline.AddInterpFloat(TurnCurve,Update);
		TurnTimeline.SetTimelineFinishedFunc(Finish);
		TurnTimeline.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
		TurnTimeline.SetLooping(false);
	}
}

void AMari::Look(const FInputActionValue& Value)
{
	DoLook(Value.Get<FVector2D>().X,Value.Get<FVector2D>().Y);
}

void AMari::MoveStart()
{
	TurnTime = 0.0f;
}

void AMari::DoMove(float Right, float Forward)
{
	if (GetController()!=nullptr)
	{
		TurnTime+=deltaTime;
		
		FRotator Rotation = GetController()->GetControlRotation();
		FRotator Walk = {0,Rotation.Yaw,0};
		FVector FowardVector = FRotationMatrix(Walk).GetUnitAxis(EAxis::Y);
		FVector RightVector = FRotationMatrix(Walk).GetUnitAxis(EAxis::X);
		// AddMovementInput(FowardVector,Forward);
		// AddMovementInput(RightVector,Right);
		FVector2D input(Right,Forward);
		MoveInputAmount = input.Size();
		MoveInputAmount = FMath::Clamp(MoveInputAmount,0.0f,1.0f);
		
		TurnDirection = FowardVector*Forward+RightVector*Right;
		if (TurnDirection.IsNearlyZero()) return;
		TurnDirection.Normalize();
		//AddMovementInput(TurnDirection,1.0f);
		//StartTurnTo(direction);
	}
}

void AMari::MoveEnd()
{
	if (TurnTime <0.1f)
	StartTurnTo(TurnDirection);
}

void AMari::DoLook(float Yaw, float Pitch)
{
	if (GetController()!=nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AMari::DoJumpStart()
{
	Jump();
}

void AMari::DoJumpEnd()
{
	StopJumping();
}

void AMari::RunStart()
{
	GetCharacterMovement()->MaxWalkSpeed  = 500.0f;
}
void AMari::RunEnd()
{
	GetCharacterMovement()->MaxWalkSpeed  = 300.0f;
}

void AMari::UpdateTurn(float Alpha)
{
	FRotator Rotation = FMath::InterpEaseInOut(TurnStart,TurnEnd,Alpha,2.0f);
	SetActorRotation(Rotation);
}

void AMari::FinishTurn()
{
	SetActorRotation(TurnEnd);
}

void AMari::StartTurnTo(const FVector& Direction)
{
	if (Direction.IsNearlyZero()) return;
	FVector NewDir = Direction.GetSafeNormal();
	if (FVector::DotProduct(LastTurnDir,NewDir)>0.98f) return;
	LastTurnDir = NewDir;
	TurnStart = GetActorRotation();
	TurnEnd = {0.f,Direction.Rotation().Yaw,0.f};
	TurnTimeline.PlayFromStart();
}

void AMari::DoJump(const FVector2D &jumpGravityScale)
{
	if (GetCharacterMovement()->IsFalling())
	{
		if (GetVelocity().Z>0.f)
			GetCharacterMovement()->GravityScale = jumpGravityScale.Y;
		else
			GetCharacterMovement()->GravityScale = jumpGravityScale.X;
	}
	else
	{
		GetCharacterMovement()->GravityScale = jumpGravityScale.X;
	}
}

// Sets default values
AMari::AMari()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->SetCapsuleRadius(16.0f);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation=true;
	// SpringArmComponent->bEnableCameraLag = true;
	// SpringArmComponent->bEnableCameraRotationLag = true;
	
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation=true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetMesh()->SetRelativeLocation({0,0,-88});
	GetMesh()->SetRelativeRotation({0,-90,0});
	GetMesh()->SetRelativeScale3D(FVector{0.1f,0.1f,0.1f});
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.6f;
	GetCharacterMovement()->JumpZVelocity = 350.0f;
	JumpMaxCount = 2;
	JumpMaxHoldTime = 0.2f;
	

}



// Called every frame
void AMari::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaTime = DeltaTime;
	
	TurnTimeline.TickTimeline(DeltaTime);
	DoJump(JumpGravityScale);

}

// Called to bind functionality to input
void AMari::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started,this,&AMari::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this,&AMari::DoJumpEnd);
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Started,this,&AMari::MoveStart);
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AMari::Move);
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Completed,this,&AMari::MoveEnd);
		EnhancedInputComponent->BindAction(MouseLookAction,ETriggerEvent::Triggered,this,&AMari::Look);
		EnhancedInputComponent->BindAction(RunAction,ETriggerEvent::Started,this,&AMari::RunStart);
		EnhancedInputComponent->BindAction(RunAction,ETriggerEvent::Completed,this,&AMari::RunEnd);
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OvO"));
	}

}

