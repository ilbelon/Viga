

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/JumpInterface.h"
#include "Core/Interfaces/AttackInterface.h"
#include "Core/Interfaces/DamageableInterface.h"
#include "GameFramework/Character.h"
#include "VigaCharacter.generated.h"

//class UHealthComponent;
UCLASS()
class VIGA_API AVigaCharacter : public ACharacter, public IJumpInterface, public IAttackInterface, public IDamageableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVigaCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//--PARTE GESTIONE SALTO--//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Input")
	bool bWantsToJump = 0;
	//jumpInterface
	virtual void WantsToJump() override;
	virtual void HandleJumpNotify() override;
	//--FINE PARTE GESTIONE SALTO--//
	
	//--PARTE GESTIONE ATTACCO--//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackMontage;
	//AttackInterface
	virtual void Attack() override;
	virtual void AttackCollisionCanStartOverlap() override;
	virtual void AttackCollisionEndOverlap() override;
	//Delegate
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//set nemici
	TSet<TObjectPtr<AActor>> AlreadyHitActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UCapsuleComponent> AttackCollisionCapsule;

	//Damageable interface
	virtual void ApplyDamage(int32 DamageAmount, AActor* DamageInstigator) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TObjectPtr<UHealthComponent> HealthComponent;

	UFUNCTION()
	void OnHealthChange(int32 NewHealth);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	int32 BaseDamage = 1;

	


	UFUNCTION()
	void OnDeath();

	//parte per animazione morte e delegate
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathMontage;
	FOnMontageEnded EndedDelegate;


	//--FINE PARTE GESTIONE ATTACCO--//

private:
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
