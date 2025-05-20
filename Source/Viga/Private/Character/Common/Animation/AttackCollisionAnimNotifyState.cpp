// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Common/Animation/AttackCollisionAnimNotifyState.h"
#include "Core/Interfaces/AttackInterface.h"

void UAttackCollisionAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    if (!MeshComp) return;
    UObject* Owner = MeshComp->GetOwner();

    if (Owner && Owner->GetClass()->ImplementsInterface(UAttackInterface::StaticClass()))
    {
        //  IJumpInterface
        IAttackInterface* AttackOwner = Cast<IAttackInterface>(Owner);
        if (AttackOwner)
        {
            AttackOwner->AttackCollisionCanStartOverlap();
        }
    }
}

void UAttackCollisionAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (!MeshComp) return;
    UObject* Owner = MeshComp->GetOwner();

    if (Owner && Owner->GetClass()->ImplementsInterface(UAttackInterface::StaticClass()))
    {
        //  IJumpInterface
        IAttackInterface* AttackOwner = Cast<IAttackInterface>(Owner);
        if (AttackOwner)
        {
            AttackOwner->AttackCollisionEndOverlap();
        }
    }
}