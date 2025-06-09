


#include "Character/VigaCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Character/HealthComponent.h"


// Sets default values
AVigaCharacter::AVigaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackCollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollisionCapsule"));
	AttackCollisionCapsule->SetupAttachment(GetMesh(), TEXT("LeftHandSocket"));

	AttackCollisionCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollisionCapsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AttackCollisionCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	AttackCollisionCapsule->SetCapsuleHalfHeight(7580.f);
	AttackCollisionCapsule->SetCapsuleRadius(2439.f);
	AttackCollisionCapsule->SetRelativeLocation(FVector(0.f, 0.f, 7000.f));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	//AddOwnedComponent(HealthComponent);

}

// Called when the game starts or when spawned
void AVigaCharacter::BeginPlay()
{
	Super::BeginPlay();
	JumpMaxCount = 2;
	AttackCollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AVigaCharacter::OnComponentBeginOverlap);
	HealthComponent->OnHealthChangeTriggered.AddDynamic(this, &AVigaCharacter::OnHealthChange);
	HealthComponent->OnDeathTriggered.AddDynamic(this, &AVigaCharacter::OnDeath);
	
	//In Blueprint c'è il nodo che gestisce i delegate del montage ended e gli altri
	//in c++ bisogna dichiararlo così in questo modo si può usare il delegate per il respawn
	EndedDelegate.BindUObject(this, &AVigaCharacter::OnMontageEnded);
	
	//Questa soluzione sotto andrebbe bene per gestire TUTTI i montage, ma si dovrebbe andare a controllare 
	//quale montage usare ogni volta. Siccome serve solo per il death non ha senso controllarli tutti
	//lascio questo come riferimento
	/*if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AVigaCharacter::OnMontageEnded);
	}*/
	
}

// Called every frame
void AVigaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVigaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AVigaCharacter::WantsToJump()
{
	if (JumpCurrentCount == 0) 
	{
		bWantsToJump = true;
	}
	else if (JumpCurrentCount == 1) 
	{
		Jump();
	}
}

void AVigaCharacter::HandleJumpNotify()
{
	if (JumpCurrentCount == 0) 
	{
		Jump();
		bWantsToJump = 0;
	}
}

void AVigaCharacter::Attack()
{
	if (!GetMesh()) return;
	if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage) && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(DeathMontage))
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
	}
}

void AVigaCharacter::AttackCollisionCanStartOverlap()
{
	AttackCollisionCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AVigaCharacter::AttackCollisionEndOverlap()
{
	AttackCollisionCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AlreadyHitActors.Empty();
}

void AVigaCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this || AlreadyHitActors.Contains(OtherActor)) {
		if (OtherActor->GetClass()->ImplementsInterface(UDamageableInterface::StaticClass())) {
			IDamageableInterface* Damageable = Cast<IDamageableInterface>(OtherActor);
			if (Damageable) {
				UE_LOG(LogTemp, Warning, TEXT("Hitted %s"), *OtherActor->GetName());
				UE_LOG(LogTemp, Warning, TEXT("OtherComp %s"), *OtherComp->GetName());
				Damageable->ApplyDamage(BaseDamage, this);
			}
		}
		return;
	}
	AlreadyHitActors.Add(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("Overlapped %s"), *OtherActor->GetName());


}

void AVigaCharacter::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AVigaCharacter::ApplyDamage(int32 DamageAmount, AActor* DamageInstigator)
{
	//il broadcast dell'evento avviene nel modifyhealth, quindi sul component
	//sarebbe stato uguale se qui avessi messo HealthComponent->TriggerOnHealthChange(HealthComponent->GetCurrentHealth());
	//ma essendo già nel component non serve
	HealthComponent->ModifyHealth(-DamageAmount);
	
}

void AVigaCharacter::OnHealthChange(int32 NewHealth)
{
	if (NewHealth == 0) {
		UE_LOG(LogTemp, Warning, TEXT("MORTO"));
		HealthComponent->TriggerOnDeath();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Vita: %d"), HealthComponent->GetCurrentHealth());
	}
}

void AVigaCharacter::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("OnDeath"));
	if (DeathMontage!=nullptr) {
		if (GetMesh() && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(DeathMontage))
		{
			GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage);
			//Attenzione: Montage_SetEndDelegate deve essere chiamato dopo Montage_Play, non prima, perché Unreal associa 
			// il delegate alla singola riproduzione.
			GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(EndedDelegate, DeathMontage);
		}
	}
}

void AVigaCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted) 
{
	UE_LOG(LogTemp, Warning, TEXT("RESPAWNA SHOEBILL PER IL POTERE DI GREYSKULL"));
}


