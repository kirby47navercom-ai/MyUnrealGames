// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MariController.generated.h"

/**
 * 
 */

class UInputMappingContext;

UCLASS()
class GAMEENGINE1PROJECT_API AMariController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputMappingContext* DefaultMappingContexts;
	
	virtual void SetupInputComponent() override;
	
	
	
};
