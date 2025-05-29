


#include "Character/Enemy/VigaEnemyBase.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
AVigaEnemyBase::AVigaEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("EnemyCollision"));
	EnemyCollision->SetupAttachment(RootComponent);

	EnemyWakeUpCollision = CreateDefaultSubobject<USphereComponent>(TEXT("EnemyWakeUpCollision"));
	EnemyWakeUpCollision->SetSphereRadius(540.f);
	EnemyWakeUpCollision->SetupAttachment(RootComponent);

	EnemyAggroCollision = CreateDefaultSubobject<USphereComponent>(TEXT("EnemyAggroCollision"));
	EnemyAggroCollision->SetSphereRadius(318.f);
	EnemyAggroCollision->SetupAttachment(RootComponent);

	EnemyAttackHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackHitboxCollision"));
	EnemyAttackHitbox->SetupAttachment(RootComponent);

	/*TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetupAttachment(RootComponent);*/

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AVigaEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVigaEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVigaEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


