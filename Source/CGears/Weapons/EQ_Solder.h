// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "EQ_Solder.generated.h"

/**
 * 
 */
UCLASS()
class CGEARS_API AEQ_Solder : public AWeapon
{
	GENERATED_BODY()

public:

	AEQ_Solder();

	virtual void Fire() override;

	
};
