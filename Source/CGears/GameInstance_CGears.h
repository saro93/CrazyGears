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


        TArray<int32> Ammo;
	    TArray<int32> MaxAmmo;


};