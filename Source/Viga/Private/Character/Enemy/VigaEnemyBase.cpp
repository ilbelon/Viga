


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
	EnemyAttackHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EnemyAttackHitbox->SetupAttachment(RootComponent);

	/*TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetupAttachment(RootComponent);*/

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AVigaEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	EnemyAttackHitbox->OnComponentBeginOverlap.AddDynamic(this, &AVigaEnemyBase::OnComponentBeginOverlap);
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

void AVigaEnemyBase::Attack()
{
	if (GetMesh() && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
	{
		//perché l'animazione parta occorre che l'animation blueprint abbia lo slot impostato 
		// sullo stesso slot selezionato nell'animation montage
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
		//GetMesh()->GetAnimInstance()->OnPlayMontageNotifyEnd.AddDynamic( sdd)
		/* UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(
			Mesh,
			VaultMontage
		);

		PlayMontageCallbackProxy->OnCompleted.AddDynamic(this, &UVaultComponent::OnVaultMontageCompleted);*/
	}
}

void AVigaEnemyBase::AttackCollisionCanStartOverlap()
{
	EnemyAttackHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AVigaEnemyBase::AttackCollisionEndOverlap()
{
	EnemyAttackHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AVigaEnemyBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Colpito %s"), *OtherActor->GetName());
}

void AVigaEnemyBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


