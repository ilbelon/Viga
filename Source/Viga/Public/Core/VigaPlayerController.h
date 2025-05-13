

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VigaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class VIGA_API AVigaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AVigaPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Variables")
	float RotationInterpolationSpeed = 8.f;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> ShoebillContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	
	void Move(const FInputActionValue& InputActionValue);

	void Look(const FInputActionValue& InputActionValue);
};
