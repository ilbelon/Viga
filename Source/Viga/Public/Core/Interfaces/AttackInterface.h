

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "AttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VIGA_API IAttackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void Attack() = 0;

	virtual void AttackCollisionCanStartOverlap() = 0;

	virtual void AttackCollisionEndOverlap() = 0;
};
