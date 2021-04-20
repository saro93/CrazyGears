// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Esplosione.generated.h"

UCLASS()
class CGEARS_API AEsplosione : public AActor
{
	GENERATED_BODY()
	

		


public:	
	// Sets default values for this actor's properties
	AEsplosione();

	UPROPERTY(EditDefaultsOnly,Category="Parametri")
	    float RaggioEsplosione;

	UPROPERTY(EditDefaultsOnly, Category = "Parametri")
		float PotenzaRadiale;

	UPROPERTY(EditdefaultsOnly, Category = "Parametri")
		UParticleSystem* Effetto;
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		class URadialForceComponent* ForzaEsplosiva;
	UPROPERTY()
		USceneComponent* Point;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
