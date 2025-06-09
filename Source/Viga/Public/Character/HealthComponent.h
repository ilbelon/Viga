// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


// Dichiarazione del delegato
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathTriggered);

// Delegato con un parametro: una stringa in questo caso
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChange, int32, NewHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIGA_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Proprietà del delegato
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeathTriggered OnDeathTriggered;

	// Metodo per attivare il delegato
	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerOnDeath();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChange OnHealthChangeTriggered;

	UFUNCTION(BlueprintCallable)
	void TriggerOnHealthChange(const int32& NewHealth);

	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ModifyHealth(int32 Delta);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	int32 MaxHealth = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	int32 CurrentHealth = 1;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
