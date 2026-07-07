// Fill out your copyright notice in the Description page of Project Settings.


#include "R1Player.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AR1Player::AR1Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	
	SpringArm->TargetArmLength = 700.0f;
	SpringArm->SetRelativeRotation({-30,0,0});
	
	
	GetMesh()->SetRelativeLocationAndRotation({0,0,-88},{0,-90,0});
}

// Called when the game starts or when spawned
void AR1Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AR1Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



