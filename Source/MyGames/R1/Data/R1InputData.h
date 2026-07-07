// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"
#include "R1InputData.generated.h"

/**
 * 
 */
class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FR1InputAction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FGameplayTag InputTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputAction = nullptr;
	
};

UCLASS(BlueprintType)
class MYGAMES_API UR1InputData : public UDataAsset
{
	GENERATED_BODY()
public:
	const UInputAction* FindInputActionByTag(const FGameplayTag& InputTag) const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FR1InputAction> InputActions;
	
};
