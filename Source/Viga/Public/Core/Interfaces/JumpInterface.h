

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "JumpInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJumpInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VIGA_API IJumpInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void WantsToJump()=0;
	virtual void HandleJumpNotify() = 0;
};
