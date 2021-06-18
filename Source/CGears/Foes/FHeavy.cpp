// Fill out your copyright notice in the Description page of Project Settings.


#include "FHeavy.h"

// Sets default values
AFHeavy::AFHeavy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFHeavy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFHeavy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFHeavy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

