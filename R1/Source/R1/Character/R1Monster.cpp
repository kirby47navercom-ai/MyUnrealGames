#include "Character/R1Monster.h"
#include "AbilitySystem//R1AbilitySystemComponent.h"

AR1Monster::AR1Monster()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	AbilitySystemComponent = CreateDefaultSubobject<UR1AbilitySystemComponent>("AbilitySystem");
	//AbilitySystemComponent->SetIsReplicated(true);
}

void AR1Monster::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystem();

}

void AR1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AR1Monster::InitAbilitySystem()
{
	Super::InitAbilitySystem();
	
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}
