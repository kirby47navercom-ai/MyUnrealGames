// Fill out your copyright notice in the Description page of Project Settings.


#include "R1Actor.h"

#include "R1LogChannels.h"
#include "../../Intermediate/Build/Win64/x64/UnrealEditor/Development/MyGames/Definitions.MyGames.h"

// Sets default values
AR1Actor::AR1Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AR1Actor::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogMyGamesR1, Warning, TEXT("AR1Actor::BeginPlay()"));
	GEngine -> ForceGarbageCollection(true);
}

// Called every frame
void AR1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

