// Fill out your copyright notice in the Description page of Project Settings.


#include "R1Actor.h"

#include "R1LogChannels.h"
#include "../../Intermediate/Build/Win64/x64/UnrealEditor/Development/MyGames/Definitions.MyGames.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AR1Actor::AR1Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = Body;
	Body->SetRelativeScale3D({2,3,0.5});
	
	Wing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wing"));
	Wing->SetupAttachment(Body);
	Wing->SetRelativeLocationAndRotation({55,-72,80},{0,90,0});
	Wing->SetRelativeScale3D({3.75f,0.25f,0.5f});
	
	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(Body);
	Head->SetRelativeLocationAndRotation({105,36,40},{0,0,0});
	Head->SetRelativeScale3D({0.25f,0.25f,0.25f});
	
	Wing->SetRelativeLocation({0,0,0});
	Head->SetRelativeLocation({0,0,0});
	
	
}

// Called when the game starts or when spawned
void AR1Actor::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogMyGamesR1, Warning, TEXT("AR1Actor::BeginPlay()"));
	GEngine -> ForceGarbageCollection(true);
	
	TArray<AActor*>Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Rookiss"), Actors);
	if (Actors.Num() > 0)
	{
		Target = Actors[0];
	}
	
}

// Called every frame
void AR1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//float Speed = 50.0f;
	//float Distance = DeltaTime*Speed;
	//
	//FVector Location = GetActorLocation();
	//FVector Direction = Target->GetActorLocation() - GetActorLocation();
	//Direction.Normalize();
	//AddActorWorldOffset(Direction*Distance);
	
	
	//FVector NewLocation = Location + FVector::ForwardVector*Distance;
	//SetActorLocation(NewLocation);
	//AddActorWorldOffset(FVector::ForwardVector*Distance)
}

