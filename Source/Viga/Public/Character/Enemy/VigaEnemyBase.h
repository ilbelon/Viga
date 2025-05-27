

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VigaEnemyBase.generated.h"

class USphereComponent;
class USplineComponent;

UCLASS()
class VIGA_API AVigaEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
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
	USplineComponent* MovementSpline;
	
};
