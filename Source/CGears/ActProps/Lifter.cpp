// Fill out your copyright notice in the Description page of Project Settings.


#include "Lifter.h"
#include "Components/BoxComponent.h"
#include "CGears/Character/CGearsRobot.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "CGears/GameInstance_CGears.h"


// Sets default values
ALifter::ALifter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	distance = 408;

	stato    = 0;

	mode     = 0;

	//delay    = 10000;
	
	//active   = false;

	Stat = CreateDefaultSubobject<USceneComponent>(TEXT("Stat"));
	RootComponent = Stat;

	Mov = CreateDefaultSubobject<USceneComponent>(TEXT("Mov"));
	Mov->SetupAttachment(Stat);

	

	terminalA = CreateDefaultSubobject<UBoxComponent>(TEXT("terminalA"));
	terminalA->SetupAttachment(RootComponent);

	terminalB = CreateDefaultSubobject<UBoxComponent>(TEXT("terminalB"));
	terminalB->SetupAttachment(Mov);

	FName upper[3] = { "Base","handle","console"};

	for (int i = 0; i < 3; i++)
	{
		Mobile.Add(CreateDefaultSubobject<UStaticMeshComponent>(upper[i]));
		Mobile[i]->SetupAttachment(Mov);
	}

	FName down[8] = { "Start","Exhandle","Tile0","Tile1","Tile2","Tile3","Tile4","Tile5" };

	for (int i = 0; i < 8; i++)
	{
		Static.Add(CreateDefaultSubobject<UStaticMeshComponent>(down[i]));
		Static[i]->SetupAttachment(Stat);
	}

}

// Called every frame
void ALifter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



		switch (stato)
		{

		case 0: // static Down
		{
			if (Key)
			{
				if (Key->bAction)
				{
					stato = 1;

					SActual = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SMove, GetActorLocation());

				}
			}

		}
		break;

		case 1: // lift
		{
			if (Mov->GetRelativeLocation().Z < distance)
			{

				Mov->SetRelativeLocation(Mov->GetRelativeLocation() + FVector(0, 0, 100 * DeltaTime));
			}
			else
			{
				if (SActual)
				{
					SActual->Stop();
					SActual = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SStop, GetActorLocation());
				}
				stato = 2;
			}
		}
		break;

		case 2: // static Up
		{
			if (Key)
			{
				if (Key->bAction)
				{
					stato = 3;

					SActual = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SMove, GetActorLocation());



				}

			}
		}
		break;

		case 3: // falling
		{
			if (Mov->GetRelativeLocation().Z > 0)
			{

				Mov->SetRelativeLocation(Mov->GetRelativeLocation() - FVector(0, 0, 100 * DeltaTime));
			}
			else {

				//stato = 0;
				if (SActual)
				{
					SActual->Stop();
					UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SStop, GetActorLocation());

				}
				stato = 0;
			}
			break;

		}
		}
	
	


}

void ALifter::Activate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto GI = Cast<UGameInstance_CGears>(GetGameInstance());

	if ((GI && GI->bElevatorActive)   || mode == 1)
	{
		auto temp = Cast<ACGearsRobot>(OtherActor);

		if (temp)
		{
			//active = true;
			Key = temp;
		}
	}
}

void ALifter::DeActivate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto GI = Cast<UGameInstance_CGears>(GetGameInstance());

	if ((GI && GI->bElevatorActive) || mode == 1)
	{
		auto temp = Cast<ACGearsRobot>(OtherActor);

		if (temp)
		{
		Key = nullptr;
		}
	}
}

void ALifter::BeginPlay()
{
	Super::BeginPlay();
	terminalA->OnComponentBeginOverlap.AddDynamic(this, &ALifter::Activate);
	terminalB->OnComponentBeginOverlap.AddDynamic(this, &ALifter::Activate);
	terminalA->OnComponentEndOverlap.AddDynamic(this, &ALifter::DeActivate);
	terminalB->OnComponentEndOverlap.AddDynamic(this, &ALifter::DeActivate);


	if (mode == 1)
	{
		FVector Actual = Mov->GetRelativeLocation();
		Actual.Z = distance;
		Mov->SetRelativeLocation(Actual);
		stato = 2;
	}

}
