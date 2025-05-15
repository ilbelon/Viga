


#include "Character/VigaCharacter.h"
#include "Components/CapsuleComponent.h"


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
	AttackCollisionCapsule->SetCapsuleRadius(2439.f);//7000,0
	AttackCollisionCapsule->SetRelativeLocation(FVector(0.f, 0.f, 7000.f));

}

// Called when the game starts or when spawned
void AVigaCharacter::BeginPlay()
{
	Super::BeginPlay();
	JumpMaxCount = 2;
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
	if (GetMesh() && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
	}
}


