// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Task/UBTT_MoveAlongSpline.h"
#include "Character/Enemy/VigaEnemyBase.h"
#include "Components/SplineComponent.h"
#include "AIController.h"

// GUARDATE BENE QUI, RITORNO LA MIA STRUCT, P.S SE DEVO AGGIUNGERE PIU' VARIABILI RELATIVE AL NODO CHE SERVONO 
// NEL TASK LE AGGIUNGO ALLA STRUCT
uint16 UBTT_MoveAlongSpline::GetSpecialMemorySize() const
{
	return sizeof(FMoveAlongSplineMemory);
}

UBTT_MoveAlongSpline::UBTT_MoveAlongSpline()
{
	NodeName = TEXT("CPP_MoveAlongSpline");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_MoveAlongSpline::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/*FMoveAlongSplineMemory* Memory = (FMoveAlongSplineMemory*)NodeMemory;

	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Aborted;

	AVigaEnemyBase* EnemyRef = Cast<AVigaEnemyBase>(AICon->GetPawn());
	if (!EnemyRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn is null in ExecuteTask!"));
		return EBTNodeResult::Aborted;
	}

	Memory->Enemy = EnemyRef;


	return EBTNodeResult::InProgress;*/

	FMoveAlongSplineMemory* Memory = (FMoveAlongSplineMemory*)NodeMemory;

	// Inizializza/Resetta la memoria specifica del nodo
	Memory->DistanceAlongSpline = 0.f; // CRUCIALE per ogni nuova esecuzione
	Memory->Enemy = nullptr; // Inizializza anche il puntatore

	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Aborted;

	AVigaEnemyBase* EnemyRef = Cast<AVigaEnemyBase>(AICon->GetPawn());
	if (!EnemyRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn is null in ExecuteTask!"));
		return EBTNodeResult::Aborted;
	}

	Memory->Enemy = EnemyRef; // Assegna dopo il check

	// Se MovementSpline è necessario già in Execute per qualche check, fallo qui
	// Altrimenti, il check in TickTask va bene

	return EBTNodeResult::InProgress;
}

void UBTT_MoveAlongSpline::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FMoveAlongSplineMemory* Memory = (FMoveAlongSplineMemory*)NodeMemory;

	if (!Memory || !Memory->Enemy) // <--- CONTROLLA SEMPRE PRIMA
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	AVigaEnemyBase* Enemy = Memory->Enemy.Get();
	if (!Enemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_MoveAlongSpline: Enemy is null in TickTask. Failing task."));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}


	if (!Enemy->MovementSpline)
	{
		UE_LOG(LogTemp, Error, TEXT("MovementSpline is nullptr!"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	Memory->DistanceAlongSpline += Enemy->SpeedSpline * DeltaSeconds;

	float SplineLength = Enemy->MovementSpline->GetSplineLength();

	float ModDistance = FMath::Fmod(Memory->DistanceAlongSpline, SplineLength);

	FVector TargetLocation = Enemy->MovementSpline->GetLocationAtDistanceAlongSpline(ModDistance, ESplineCoordinateSpace::World);
	FVector Direction = (TargetLocation - Enemy->GetActorLocation()).GetSafeNormal();

	Enemy->AddMovementInput(Direction, 1.0f);

	if (!Direction.IsNearlyZero())
	{
		FRotator TargetRotation = Direction.Rotation();
		FRotator CurrentRotation = Enemy->GetActorRotation();

		FRotator NewRotation = FRotator(0.f, TargetRotation.Yaw, 0.f);

		FRotator InterpolatedRotation = FMath::RInterpTo(CurrentRotation, NewRotation, DeltaSeconds, 5.f);
		Enemy->SetActorRotation(FRotator(0.f, InterpolatedRotation.Yaw, 0.f));
	}

	//FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
}

EBTNodeResult::Type UBTT_MoveAlongSpline::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory); // Chiama la base

	UE_LOG(LogTemp, Warning, TEXT("CPP_MoveAlongSpline::AbortTask() è stata chiamata!"));

	// FinishLatentAbort() non è più necessaria qui se AbortTask ritorna direttamente Aborted
	// e la task non ha operazioni "latent" complesse da fermare durante l'aborto.
	// La documentazione o l'uso comune è che AbortTask stesso segnali l'aborto
	// ritornando EBTNodeResult::Aborted.
	// FinishLatentAbort è più per le task che sono InProgress e devono essere
	// esplicitamente portate a uno stato di aborto completato.
	// Tuttavia, se la task base gestisce la logica di aborto latente, 
	// chiamare Super::AbortTask e ritornare EBTNodeResult::Aborted dovrebbe essere sufficiente.

	// Se la task è una task "semplice" che può essere interrotta immediatamente,
	// ritornare EBTNodeResult::Aborted è il modo standard.
	// Se la task avesse avviato qualche operazione asincrona che deve essere pulita,
	// qui sarebbe il posto per farlo prima di ritornare.

	if (OwnerComp.GetTaskStatus(this) == EBTTaskStatus::Active) // Controlla se era attiva (cioè, in tick)
	{
		FinishLatentAbort(OwnerComp);
	}
	//

	// Per una task come questa, che semplicemente smette di essere tickata,
	// ritornare Aborted è corretto.
	return EBTNodeResult::Aborted;
}