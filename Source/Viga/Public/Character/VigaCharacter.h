

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/JumpInterface.h"
#include "Core/Interfaces/AttackInterface.h"
#include "Core/Interfaces/DamageableInterface.h"
#include "GameFramework/Character.h"
#include "VigaCharacter.generated.h"

class UHealthComponent;


UCLASS()
class VIGA_API AVigaCharacter : public ACharacter, public IJumpInterface, public IAttackInterface, public IDamageableInterface
{
	GENERATED_BODY()

public:
	/*Funzioni base*/
	// Sets default values for this character's properties
	AVigaCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*Parte gestione salto*/
	
	//Variabile utilizzata per gestire il tempo che intercorre tra la pressione del tasto e il salto vero e proprio nell'animazione 
	//che avviene dopo una prima fase di "preparazione". Non è ottimale per un platform ma così l'animazione è coerente con lo stacco
	//da terra
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Input")
	bool bWantsToJump = 0;
	//jumpInterface

	virtual void WantsToJump() override;
	virtual void HandleJumpNotify() override;
	//jumpinterfaceEnd
	/*FINE PARTE GESTIONE SALTO*/
	/*PARTE GESTIONE ATTACCO*/
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackMontage;

	//AttackInterface

	virtual void Attack() override;
	virtual void AttackCollisionCanStartOverlap() override;
	virtual void AttackCollisionEndOverlap() override;

	//Delegates
	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	//set nemici
	TSet<TObjectPtr<AActor>> AlreadyHitActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	
	//Collisione sl braccio dello shoebill
	TObjectPtr<UCapsuleComponent> AttackCollisionCapsule;

	//Danno base inflitto
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	int32 BaseDamage = 1;

	//--FINE PARTE GESTIONE ATTACCO--//

	//--PARTE GESTIONE DANNI SUBITI--//

	//Damageable interface
	virtual void ApplyDamage(int32 DamageAmount, AActor* DamageInstigator) override;

	//Component per gestire gli eventi OnDamageTaken e OnDeath
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TObjectPtr<UHealthComponent> HealthComponent;

	//Di seguito le funzioni utilizzate dai due eventi gestiti con l'health component

	UFUNCTION()
	void OnHealthChange(int32 NewHealth);

	UFUNCTION()
	void OnDeath();
	
	

	//Death Montage per l'animazione
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathMontage;
	
	//Delegate per la fine dell'animazione della morte
	FOnMontageEnded EndedDelegate;

	//funzione utilizzata dal delegate per il montage ended
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	

	//--FINE PARTE GESTIONE DANNI SUBITI--//
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
