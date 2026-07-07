// Fill out your copyright notice in the Description page of Project Settings.


#include "R1Monster.h"

// Sets default values
AR1Monster::AR1Monster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AR1Monster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AR1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input


