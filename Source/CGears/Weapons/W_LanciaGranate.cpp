// Fill out your copyright notice in the Description page of Project Settings.


#include "W_LanciaGranate.h"
#include "Granata.h"
#include "CGears/Componenti/HealthComponent.h"

AW_LanciaGranate::AW_LanciaGranate()
{

	
	
	Consumo = 5;
}

void AW_LanciaGranate::Fire()
{


	if (OwnerHealth->energia > 0 && ToSpawn)
	{
		OwnerHealth->energia -= Consumo;

		GetWorld()->SpawnActor<AGranata>
			(ToSpawn, GetWeapon()->GetSocketLocation(TEXT("Muzzle")), GetActorForwardVector().Rotation());
	}

}
