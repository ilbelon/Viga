// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/VigaAIController.h"

void AVigaAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    bStartAILogicOnPossess = true;
    //bStartLogicAutomatically = true
    //StartLogic(); // opzionale, solo se non automatico
}
