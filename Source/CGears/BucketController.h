// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BucketController.generated.h"

/**
 * 
 */
UCLASS()
class CGEARS_API ABucketController : public AAIController
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void SwitchCharacter(APawn* newTarget);
};
