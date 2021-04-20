// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_NelRaggio.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"

void UBTService_NelRaggio::TickNode(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMedory, float DeltaSecond)
{

	auto Controller = OwnerComponent.GetAIOwner();
	auto MyRobot = Controller->GetPawn();
	auto lavagna = OwnerComponent.GetBlackboardComponent();
	auto otherPawn = Cast<APawn>(lavagna->GetValueAsObject(PawnRef.SelectedKeyName));

	if (MyRobot && otherPawn)
	{

		if((MyRobot->GetActorLocation() - otherPawn->GetActorLocation()).Size()>Raggio)
		{
			lavagna->SetValueAsBool(bRaggio.SelectedKeyName,false);
	    }
		else
		{
			lavagna->SetValueAsBool(bRaggio.SelectedKeyName,true);
		}
	}
}
