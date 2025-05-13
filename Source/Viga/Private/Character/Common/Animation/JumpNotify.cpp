// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Common/Animation/JumpNotify.h"
#include "Core/Interfaces/JumpInterface.h"


void UJumpNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (!MeshComp) return;
    UObject* Owner = MeshComp->GetOwner();
    
    if (Owner && Owner->GetClass()->ImplementsInterface(UJumpInterface::StaticClass()) )
    {
       //  IJumpInterface
        IJumpInterface* JumpOwner = Cast<IJumpInterface>(Owner);
        if (JumpOwner) 
        {
            JumpOwner->HandleJumpNotify();
        }
    }
}
