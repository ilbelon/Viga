

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/JumpInterface.h"
#include "Core/Interfaces/AttackInterface.h"
#include "GameFramework/Character.h"
#include "VigaCharacter.generated.h"

UCLASS()
class VIGA_API AVigaCharacter : public ACharacter, public IJumpInterface, public IAttackInterface
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
	//--FINE PARTE GESTIONE ATTACCO--//
	
	
};
