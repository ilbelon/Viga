


#include "Character/Enemy/VigaEnemyPlaceable.h"
#include "Components/SplineComponent.h"
#include "Components/SceneComponent.h"


// Sets default values
AVigaEnemyPlaceable::AVigaEnemyPlaceable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));;

	EnemyActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("EnemyActor"));
	EnemyActor->SetupAttachment(RootComponent);

	MovementSpline = CreateDefaultSubobject<USplineComponent>(TEXT("MovementSpline"));
	MovementSpline->SetupAttachment(RootComponent);
	//defaultscene component come root
	//childactor 
	//spline
}

// Called when the game starts or when spawned
void AVigaEnemyPlaceable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVigaEnemyPlaceable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


