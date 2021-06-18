// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance_CGears.generated.h"

/**
 * 
 */
UCLASS()
class CGEARS_API UGameInstance_CGears : public UGameInstance
{
	GENERATED_BODY()

public:

	UGameInstance_CGears();

	UPROPERTY(BlueprintReadWrite)
	bool bElevatorActive;

	UPROPERTY(BlueprintReadWrite)
	bool bLegActive;
	
	UPROPERTY(BlueprintReadWrite)
	bool bDoorsActive;

	UPROPERTY(BlueprintReadWrite)
	bool bSpecialActive;

};
