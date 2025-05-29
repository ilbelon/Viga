

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VigaEnemyBase.generated.h"

class USphereComponent;
class USplineComponent;
class UBoxComponent;
class UTextRenderComponent;

UCLASS()

class VIGA_API AVigaEnemyBase : public ACharacter
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	TObjectPtr<USplineComponent> MovementSpline;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<USphereComponent> EnemyWakeUpCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<USphereComponent> EnemyAggroCollision;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<UBoxComponent> EnemyAttackHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float SpeedSpline = 200.f;

	

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DistanceAlongSpline = 0.f;*/

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr <UTextRenderComponent> TextRender;*/
	
};
