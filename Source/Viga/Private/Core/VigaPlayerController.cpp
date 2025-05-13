


#include "Core/VigaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AVigaPlayerController::AVigaPlayerController()
{
	bReplicates = false;
}

void AVigaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(ShoebillContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	//check(Subsystem); Prima c'era il check, ma nel caso del multyplayer potrebbe essere chiamato sugli altri character
	//facendo crashare il gioco per cui per evitare che succeda invece del check è sufficiente usare un if
	if (Subsystem) {
		Subsystem->AddMappingContext(ShoebillContext, 0);
	}
}

void AVigaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVigaPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVigaPlayerController::Look);
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
