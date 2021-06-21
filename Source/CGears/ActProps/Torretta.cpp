// Fill out your copyright notice in the Description page of Project Settings.


#include "Torretta.h"
#include "DrawDebugHelpers.h"
#include "CGears/Character/CGearsRobot.h"

// Sets default values
ATorretta::ATorretta()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshBase=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	PiattoMobile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Piatto"));
	Cannoni = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannoni"));

	RootComponent = MeshBase;
	//MeshBase->SetupAttachment(RootComponent);
	PiattoMobile->SetupAttachment(MeshBase);
	Cannoni->SetupAttachment(PiattoMobile);

	Speed     = 10;
    
	FullMode  = true;

	Angle     = 90.f;

	MaxDetect = 1000;

	state = 0;

    Stop  = 2;

	RStop = 0;

	Aiming = false;


	DetectSize = 90.f;
}

// Called when the game starts or when spawned
void ATorretta::BeginPlay()
{
	Super::BeginPlay();
	ActualRot = PiattoMobile->GetComponentRotation();
	StartRot  = ActualRot;
}

// Called every frame
void ATorretta::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector StartP = GetActorLocation();
	FVector EndP = StartP+ActualRot.Vector() * MaxDetect;

	if (FullMode)
	{
		ActualRot.Yaw += Speed * DeltaTime;
		PiattoMobile->SetWorldRotation(ActualRot);

	}
	else
	{
		switch (state)
		{

		case 0: // move right

		ActualRot.Yaw += Speed * DeltaTime;

		PiattoMobile->SetWorldRotation(ActualRot);
		
		if (ActualRot.Yaw >= StartRot.Yaw + Angle)
		{
			RStop = Stop;
			state++;
		}

		break;

		case 1:  // stop
			if (RStop > 0) RStop -= DeltaTime;
			else
			{
				state++;
			}

		break;

		case 2:  //move right

			ActualRot.Yaw += -Speed * DeltaTime;

			PiattoMobile->SetWorldRotation(ActualRot);

			if (ActualRot.Yaw <= StartRot.Yaw - Angle)
			{
				RStop = Stop;
				state++;
			}

		break;

		case 3:  //stop
			if (RStop > 0) RStop -= DeltaTime;
			else
			{
				state = 0;
			}

		break;

		}

	}

	FHitResult MyHit;

	FColor MCol = FColor::Green;

	FCollisionShape ColCaps = FCollisionShape::MakeCapsule(40.f, abs(DetectSize));

	bool hitted = GetWorld()->SweepSingleByObjectType(MyHit, StartP + FVector(0, 0, DetectSize), EndP + FVector(0, 0, DetectSize),FQuat::Identity,ECC_Pawn, ColCaps);

	if (hitted)
	{
		auto temp = Cast<ACGearsRobot>(MyHit.GetActor());

		if (temp)
		{
			MCol = FColor::Red;
		}


	}

	//DrawDebugSphere(GetWorld(), EndP, 50, 16, FColor::Red);
	DrawDebugCapsule(GetWorld(), EndP+FVector(0,0, DetectSize), abs(DetectSize),60.f, FQuat::Identity, MCol);

}

