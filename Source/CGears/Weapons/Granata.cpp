// Fill out your copyright notice in the Description page of Project Settings.


#include "Granata.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CGears/Componenti/Esplosione.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGranata::AGranata()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));


}

// Called when the game starts or when spawned
void AGranata::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &AGranata::OnHit);

}

void AGranata::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	APawn* Tizio = Cast<APawn>(OtherActor);
	if (Tizio)
	{
		Destroy();
	}
}

void AGranata::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

    GetWorld()->SpawnActor<AActor>(Boom, GetActorLocation(), GetActorRotation());
	
}

// Called every frame
void AGranata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

