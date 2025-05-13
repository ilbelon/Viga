

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/JumpInterface.h"
#include "GameFramework/Character.h"
#include "VigaCharacter.generated.h"

UCLASS()
class VIGA_API AVigaCharacter : public ACharacter, public IJumpInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVigaCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Character|Input")
	bool bWantsToJump=0;

	virtual void WantsToJump() override;
	virtual void HandleJumpNotify() override;
	
};
