// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGearsGMPlay.generated.h"

/**
 * 
 */
UCLASS()
class CGEARS_API ACGearsGMPlay : public AGameModeBase
{
	GENERATED_BODY()
	


		public:

    APawn* char1 = nullptr;
	APawn* char2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<APawn> AllyKind;

	class ABucketController* AIcont = nullptr;

	APlayerController* PLcont = nullptr;

	virtual void BeginPlay() override;

	void SwitchTarget();

	FTimerHandle toSwap;

	void SwitchControl();

};
