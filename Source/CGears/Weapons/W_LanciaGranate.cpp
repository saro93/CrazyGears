// Fill out your copyright notice in the Description page of Project Settings.


#include "W_LanciaGranate.h"
#include "Granata.h"

AW_LanciaGranate::AW_LanciaGranate()
{

	SetAmmo(10);
	SetMaxAmmo(10);

}

void AW_LanciaGranate::Fire()
{

	if (GetAmmo() > 0 && ToSpawn)
	{
		SetAmmo(GetAmmo()-1);

		GetWorld()->SpawnActor<AGranata>
			(ToSpawn, GetWeapon()->GetSocketLocation(TEXT("Muzzle")), GetActorForwardVector().Rotation());
	}

}
