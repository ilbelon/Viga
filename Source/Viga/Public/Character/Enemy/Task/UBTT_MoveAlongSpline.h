// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UBTT_MoveAlongSpline.generated.h"

class AVigaEnemyBase;
// DEFINISCO UNA ZONA DI MEMORIA LOCALE RELATIVA AL TASK:
// 1) UNICA PER OGNI ESCUZIONE DEL NODO NEL BEHAVIOUR TREE
// 2) PERSISTENTE TRA I TICK DEL NODO
// 3) ISOLATA DALLE ALTRE ISTANZE DEL NODO
struct FMoveAlongSplineMemory
{
	float DistanceAlongSpline = 0.f;
	TObjectPtr<AVigaEnemyBase> Enemy = nullptr;
};
/**
 * 
 */
UCLASS()
class VIGA_API UBTT_MoveAlongSpline : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_MoveAlongSpline();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual uint16 GetSpecialMemorySize() const override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
