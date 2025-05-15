


#include "Core/VigaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Core/Interfaces/JumpInterface.h"
#include "Core/Interfaces/AttackInterface.h"

AVigaPlayerController::AVigaPlayerController()
{
	bReplicates = false;
}

void AVigaPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AVigaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(ShoebillContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem) {
		Subsystem->AddMappingContext(ShoebillContext, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVigaPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVigaPlayerController::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AVigaPlayerController::Jump);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AVigaPlayerController::Attack);
}

void AVigaPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (MovementVector.IsNearlyZero()) return;

	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	const FVector MoveDirection = (ForwardDirection * MovementVector.Y)+(RightDirection * MovementVector.X);
	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		//ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		//ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
		ControlledPawn->AddMovementInput(MoveDirection, 1.f);

		FRotator NewRotation = MoveDirection.Rotation();
		FRotator CurrentRotation = ControlledPawn->GetActorRotation();
		FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, NewRotation, GetWorld()->GetDeltaSeconds(), RotationInterpolationSpeed);
		ControlledPawn->SetActorRotation(SmoothRotation);
	}
		
}

void AVigaPlayerController::Look(const FInputActionValue& InputActionValue)
{
	// input is a Vector2D
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
	
}

void AVigaPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn<APawn>();
	if (ControlledPawn && ControlledPawn->GetClass()->ImplementsInterface(UJumpInterface::StaticClass())) 
	{
		IJumpInterface* JumpOwner = Cast<IJumpInterface>(ControlledPawn);
		if (JumpOwner)
		{
			JumpOwner->WantsToJump();
		}
	}
}

void AVigaPlayerController::Attack(const FInputActionValue& InputActionValue)
{
	
	APawn* ControlledPawn = GetPawn<APawn>();
	if (ControlledPawn && ControlledPawn->GetClass()->ImplementsInterface(UAttackInterface::StaticClass()))
	{
		IAttackInterface* AttackOwner = Cast<IAttackInterface>(ControlledPawn);
		if (AttackOwner)
		{
			AttackOwner->Attack();
		}
	}
}
