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


void AMari::Move(const FInputActionValue& Value)
{
	
	DoMove(Value.Get<FVector2D>().X,Value.Get<FVector2D>().Y);
	
}

void AMari::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AMari::Look(const FInputActionValue& Value)
{
	DoLook(Value.Get<FVector2D>().X,Value.Get<FVector2D>().Y);
}

void AMari::DoMove(float Right, float Forward)
{
	if (GetController()!=nullptr)
	{
		FRotator Rotation = GetController()->GetControlRotation();
		FRotator Walk = {0,Rotation.Yaw,0};
		FVector FowardVector = FRotationMatrix(Walk).GetUnitAxis(EAxis::Y);
		FVector RightVector = FRotationMatrix(Walk).GetUnitAxis(EAxis::X);
		AddMovementInput(FowardVector,Forward);
		AddMovementInput(RightVector,Right);
	}
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
	
}

void AMari::DoJumpEnd()
{
	
}

// Sets default values
AMari::AMari()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation=true;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bEnableCameraRotationLag = true;
	
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation=true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetMesh()->SetRelativeLocation({0,0,-90});
	GetMesh()->SetRelativeRotation({0,-90,0});
	GetMesh()->SetRelativeScale3D(FVector{0.1f,0.1f,0.1f});
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

}



// Called every frame
void AMari::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMari::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started,this,&AMari::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this,&AMari::DoJumpEnd);
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AMari::Move);
		EnhancedInputComponent->BindAction(MouseLookAction,ETriggerEvent::Triggered,this,&AMari::Look);
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OvO"));
	}

}

