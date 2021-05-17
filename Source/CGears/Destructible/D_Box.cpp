// Fill out your copyright notice in the Description page of Project Settings.


#include "D_Box.h"

// Sets default values
AD_Box::AD_Box()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AD_Box::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AD_Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

