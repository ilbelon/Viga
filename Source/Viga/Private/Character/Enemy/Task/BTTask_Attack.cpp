// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Task/BTTask_Attack.h"
#include "AIController.h"
#include "Core/Interfaces/AttackInterface.h"

UBTTask_Attack::UBTTask_Attack(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    NodeName = "Attack Action"; // This name will appear in the Behavior Tree editor [11, 14]
    // Initialize UPROPERTYs, set filters for FBlackboardKeySelector, etc.
    // bNotifyTick = true; // Set to true if you override TickTask [6, 15]
    // bNotifyTaskFinished = true; // Set to true if you override OnTaskFinished [6]
    // INIT_TASK_NODE_NOTIFY_FLAGS(); // Alternative macro to set bNotifyTick/bNotifyTaskFinished automatically [6, 15]
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Implement your task's core logic here.
    // This function is the entry point for the task's execution.
    // Retrieve AIController and Blackboard
    AAIController* AIController = OwnerComp.GetAIOwner();
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (!AIController || !BlackboardComp)
    {
        return EBTNodeResult::Failed; // Handle cases where components are missing
    }
    UObject* ControlledPawn = AIController->GetPawn();
    if (ControlledPawn && ControlledPawn->GetClass()->ImplementsInterface(UAttackInterface::StaticClass()))
    {
        //  IJumpInterface
        IAttackInterface* AttackOwner = Cast<IAttackInterface>(ControlledPawn);
        if (AttackOwner)
        {
            AttackOwner->Attack();
            return EBTNodeResult::InProgress;
        }
    }
    //AIController->GetPawn();

    // Example: Perform a simple action
    // AIController->MoveToLocation(FVector(0,0,0)); // Example action
    // Return Succeeded, Failed, or InProgress based on the task's outcome.
    return EBTNodeResult::Failed;
}