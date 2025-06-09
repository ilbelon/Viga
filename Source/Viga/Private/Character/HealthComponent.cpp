// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHealthComponent::TriggerOnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("OnDeathTriggered"));
	OnDeathTriggered.Broadcast();
}


void UHealthComponent::TriggerOnHealthChange(const int32& NewHealth)
{
	OnHealthChangeTriggered.Broadcast(NewHealth);
}

void UHealthComponent::ModifyHealth(int32 Delta)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0, MaxHealth);
	TriggerOnHealthChange(CurrentHealth);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

