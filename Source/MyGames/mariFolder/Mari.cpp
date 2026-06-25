// Fill out your copyright notice in the Description page of Project Settings.


#include "Mari.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include  "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


void AMari::Move(const FInputActionValue& Value)
{
	
}

void AMari::Look(const FInputActionValue& Value)
{
	
}

void AMari::DoMove(float Right, float Forward)
{
}

void AMari::DoLook(float Yaw, float Pitch)
{
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
	
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	GetMesh()->SetRelativeLocation({0,0,-90});
	GetMesh()->SetRelativeRotation({0,-90,0});
	GetMesh()->SetRelativeScale3D(FVector{0.1f,0.1f,0.1f});

}

// Called when the game starts or when spawned
void AMari::BeginPlay()
{
	Super::BeginPlay();
	
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

}

