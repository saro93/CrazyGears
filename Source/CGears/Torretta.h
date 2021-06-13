// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Torretta.generated.h"

UCLASS()
class CGEARS_API ATorretta : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorretta();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "body", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshBase = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "body", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* PiattoMobile = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "body", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Cannoni = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* boxCol;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
