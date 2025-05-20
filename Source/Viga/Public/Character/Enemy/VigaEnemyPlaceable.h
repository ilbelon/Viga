

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VigaEnemyPlaceable.generated.h"

class USplineComponent;
UCLASS()
class VIGA_API AVigaEnemyPlaceable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVigaEnemyPlaceable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Child")
	TObjectPtr<UChildActorComponent> EnemyActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	TObjectPtr <USplineComponent> MovementSpline;
	
};
