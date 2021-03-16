// Fill out your copyright notice in the Description page of Project Settings.


#include "CGearsGMPlay.h"
#include "BucketController.h"
#include "GameFramework/PlayerController.h"

void ACGearsGMPlay::BeginPlay()
{
    Super::BeginPlay();

    PLcont = GetWorld()->GetFirstPlayerController();

    if (PLcont) char1 = PLcont->GetPawn();

    if (char1) {

        FVector SpawnLoc = char1->GetActorLocation();
        SpawnLoc.X += 250;
        char2 = GetWorld()->SpawnActor<APawn>(AllyKind, SpawnLoc, char1->GetActorRotation());
    }

    if (char2) {

        AIcont = Cast<ABucketController>(char2->GetController());

        AIcont->PawnDaSeguire(char1);
    }
}

void ACGearsGMPlay::SwitchTarget()
{
    if (char1 && char2)
    {
        if (char1->IsPlayerControlled()) // se char 1 è controllato 
        {
            PLcont->SetViewTargetWithBlend
            (char2, 1.f, EViewTargetBlendFunction::VTBlend_Cubic);
        }
        else
        {
            PLcont->SetViewTargetWithBlend
            (char1, 1.f, EViewTargetBlendFunction::VTBlend_Cubic);
        }

        GetWorldTimerManager().SetTimer(toSwap, this, &ACGearsGMPlay::SwitchControl, 1.0f, false);

    }
}

void ACGearsGMPlay::SwitchControl()
{

    if (char1->IsPlayerControlled()) // se char 1 è controllato 
    {
        PLcont->Possess(char2);
        AIcont->Possess(char1);
        AIcont->PawnDaSeguire(char2);
    }
    else // se char 2 è controllato
    {
        PLcont->Possess(char1);
        AIcont->Possess(char2);
        AIcont->PawnDaSeguire(char1);
    }
}
