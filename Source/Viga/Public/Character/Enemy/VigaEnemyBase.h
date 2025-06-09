

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/Interfaces/AttackInterface.h"
#include "Core/Interfaces/DamageableInterface.h"
#include "VigaEnemyBase.generated.h"

class USphereComponent;
class USplineComponent;
class UBoxComponent;
class UTextRenderComponent;

UCLASS()

class VIGA_API AVigaEnemyBase : public ACharacter, public IAttackInterface, public IDamageableInterface
{
	GENERATED_BODY()
public:
	AVigaEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<USphereComponent> EnemyCollision;

	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<USphereComponent> EnemyWakeUpCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<USphereComponent> EnemyAggroCollision;


	

	//--PARTE GESTIONE MOVIMENTO--//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	TObjectPtr<USplineComponent> MovementSpline;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float SpeedSpline = 200.f;
	//--FINE PARTE GESTIONE MOVIMENTO--//

	//--PARTE GESTIONE ATTACCO--//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<UBoxComponent> EnemyAttackHitbox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackMontage;
	//AttackInterface
	virtual void Attack() override;
	virtual void AttackCollisionCanStartOverlap() override;
	virtual void AttackCollisionEndOverlap() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Damageable interface
	virtual void ApplyDamage(int32 DamageAmount, AActor* DamageInstigator) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TObjectPtr<UHealthComponent> HealthComponent;

	UFUNCTION()
	void OnHealthChange(int32 NewHealth);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	int32 BaseDamage = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathMontage;
	//--FINE PARTE GESTIONE ATTACCO--//

	//PARTI PRESENTI NEL CODICE DI ANDREA CHE DEVO DECIDERE SE E QUANDO INTEGRARE
	/*UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DistanceAlongSpline = 0.f;*/

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr <UTextRenderComponent> TextRender;*/
};
