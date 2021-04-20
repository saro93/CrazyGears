// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "W_LanciaGranate.generated.h"

/**
 * 
 */
UCLASS()
class CGEARS_API AW_LanciaGranate : public AWeapon
{
	GENERATED_BODY()
	
public:
		UPROPERTY(EditAnyWhere)
		TSubclassOf<class AGranata> ToSpawn;

	    AW_LanciaGranate();

	    virtual void Fire() override;

};
