// Fill out your copyright notice in the Description page of Project Settings.


#include "R1PlayerController.h"
#include "../Data/R1InputData.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyGames/R1/System/R1AssetManager.h"
#include "../R1GameplayTags.h"
#include "MyGames/R1/Character/R1Character.h"
#include "MyGames/R1/Character/R1Player.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
	


AR1PlayerController::AR1PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0;
}

void AR1PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (const UR1InputData* InputData = UR1AssetManager::GetAssetByName<UR1InputData>("InputData"))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
		}
	}

	R1Player = Cast<AR1Player>(GetCharacter());
}	

void AR1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const UR1InputData* InputData = UR1AssetManager::GetAssetByName<UR1InputData>("InputData"))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		// auto Action1 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_Move);
		// EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		//
		// auto Action2 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_Turn);
		// EnhancedInputComponent->BindAction(Action2, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);
		//
		// auto Action3 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_Jump);
		// EnhancedInputComponent->BindAction(Action3, ETriggerEvent::Triggered, this, &ThisClass::Input_Jump);
		//
		// auto Action4 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_Attack);
		// EnhancedInputComponent->BindAction(Action4, ETriggerEvent::Triggered, this, &ThisClass::Input_Attack);
		auto Action5 = InputData->FindInputActionByTag(R1GameplayTags::Input_Active_SetDestination);
		EnhancedInputComponent->BindAction(Action5, ETriggerEvent::Triggered, this, &ThisClass::OnSetDestinationTrigger);
		EnhancedInputComponent->BindAction(Action5, ETriggerEvent::Started, this, &ThisClass::OnInputStarted);
		EnhancedInputComponent->BindAction(Action5, ETriggerEvent::Completed, this, &ThisClass::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(Action5, ETriggerEvent::Canceled, this, &ThisClass::OnSetDestinationReleased);
		
		
		
		//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		//EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);
	}
}

void AR1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TickCursorTrace();

	if (GetCharacter()->GetMesh()->GetAnimInstance()->Montage_IsPlaying(nullptr) == false)
	{
		SetCreatureState(ECreatureState::Moving);
	}

	ChaseTargetAndAttack();
}

void AR1PlayerController::HandleGameplayEvent(FGameplayTag EventTag)
{
	if (EventTag.MatchesTag(R1GameplayTags::Event_Montage_Attack))
	{
		if (TargetActor)
		{
			TargetActor->OnDamaged(R1Player->FinalDamage, R1Player);
		}
	}
}

void AR1PlayerController::TickCursorTrace()
{
	if (bMousePressed)
	{
		return;
	}

	FHitResult OutCursorHit;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT OutCursorHit) == false)
	{
		return;
	}

	AR1Character* LocalHighlightActor = Cast<AR1Character>(OutCursorHit.GetActor());
	if (LocalHighlightActor == nullptr)
	{
		if (HighlightActor)
		{
			HighlightActor->UnHighlight();
		}
	}
	else
	{
		if (HighlightActor)
		{
			if (HighlightActor != LocalHighlightActor)
			{
				HighlightActor->UnHighlight();
				LocalHighlightActor->Highlight();
			}
		}
		else
		{
			LocalHighlightActor->Highlight();
		}
	}

	HighlightActor = LocalHighlightActor;
}

void AR1PlayerController::ChaseTargetAndAttack()
{
	if (TargetActor == nullptr)
	{
		return;
	}

	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}

	FVector Direction = TargetActor->GetActorLocation() - R1Player->GetActorLocation();
	if (Direction.Length() < 250.f)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Cyan, TEXT("Attack"));

		if (AttackMontage)
		{
			if (bMousePressed)
			{
				FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(R1Player->GetActorLocation(), TargetActor->GetActorLocation());
				R1Player->SetActorRotation(Rotator);

				GetCharacter()->PlayAnimMontage(AttackMontage);
				SetCreatureState(ECreatureState::Skill);

				TargetActor = HighlightActor;
			}
			else
			{
				TargetActor = nullptr;
			}
		}
	}
	else
	{
		FVector WorldDirection = Direction.GetSafeNormal();
		R1Player->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AR1PlayerController::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	if (MovementVector.X != 0)
	{
		//FVector Direction = FVector::ForwardVector * MovementVector.X;
		//GetPawn()->AddActorWorldOffset(Direction * 50.f); // * DeltaTime

		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.X);
	}

	if (MovementVector.Y != 0)
	{
		//FVector Direction = FVector::RightVector * MovementVector.Y;
		//GetPawn()->AddActorWorldOffset(Direction * 50.f); // * DeltaTime

		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
	}
}

void AR1PlayerController::Input_Turn(const FInputActionValue& InputValue)
{
	float Val = InputValue.Get<float>();
	AddYawInput(InputValue.Get<FVector2D>().X);
	AddPitchInput(InputValue.Get<FVector2D>().Y);
}

void AR1PlayerController::Input_Jump(const FInputActionValue& InputValue)
{
	if (AR1Player *Chara = Cast<AR1Player>(GetPawn()))
	Chara->Jump();
}

void AR1PlayerController::Input_Attack(const FInputActionValue& InputValue)
{
	if (AttackMontage)
	{
		Cast<AR1Player>(GetPawn())->PlayAnimMontage(AttackMontage);
	}
}

void AR1PlayerController::Input_Active_SetDestination(const FInputActionValue& InputValue)
{
	
}

void AR1PlayerController::OnInputStarted()
{
	StopMovement();
	bMousePressed = true;
	TargetActor = HighlightActor;
}

void AR1PlayerController::OnSetDestinationTrigger()
{
	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}

	if (TargetActor)
	{
		return;
	}

	FollowTime += GetWorld()->GetDeltaSeconds();
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,true,OUT Hit);
	
	if (bHitSuccessful) CachedDestination = Hit.Location;
	
	if (R1Player)
	{
		FVector WorldDirection = (CachedDestination- R1Player->GetActorLocation()).GetSafeNormal();
		R1Player->AddMovementInput(WorldDirection,1.0,false);
	}
	
	
}

void AR1PlayerController::OnSetDestinationReleased()
{
	bMousePressed = false;

	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}

	if (FollowTime<=ShortPressThreshold)
	{
		if (TargetActor == nullptr)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,CachedDestination);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,FXCursor,CachedDestination,FRotator::ZeroRotator,FVector(1.f,1.f,1.f), true, true, ENCPoolMethod::None, true);
		}
	}
	FollowTime = 0.f;
}

ECreatureState AR1PlayerController::GetCreatureState()
{
	if (R1Player)
	{
		return R1Player->CreatureState;
	}

	return ECreatureState::None;
}

void AR1PlayerController::SetCreatureState(ECreatureState InState)
{
	if (R1Player)
	{
		R1Player->CreatureState = InState;
	}
}
