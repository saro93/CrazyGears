// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Torretta.generated.h"

UCLASS()
class CGEARS_API ATorretta : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "body", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshBase = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "body", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* PiattoMobile = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "body", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Cannoni = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "body", meta = (AllowPrivateAccess = "true"))
		USceneComponent* FirePointA = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "body", meta = (AllowPrivateAccess = "true"))
		USceneComponent* FirePointB = nullptr;


	int state;

	UPROPERTY(EditAnywhere)
	float Stop;

	UPROPERTY(EditAnywhere)
	float DetectSize;

	float RStop;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FRotator ActualRot;
	FRotator StartRot;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Detect(float DeltaTime);
	// Sets default values for this actor's properties
	ATorretta();

	FTimerHandle AfterDetect;

	AActor* Detected = nullptr;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	bool  FullMode;

	UPROPERTY(EditAnywhere)
	float Angle;

	UPROPERTY(EditAnywhere)
	float MaxDetect;


};
