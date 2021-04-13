// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);

	MaxAmmo = 30;
	Ammo = MaxAmmo;
	FireRate = 0.1f;
	Damage = 10;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Fire()
{
	if (Ammo > 0)
	{
		FVector StartPoint = Weapon->GetSocketLocation(TEXT("Muzzle"));
		FVector EndPoint = StartPoint + GetActorForwardVector() * 5000;
		//DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 1.f, 0, 1.f);
		FHitResult Hit;
		FCollisionQueryParams Parametri;

		Parametri.AddIgnoredActor(this);
		Parametri.AddIgnoredActor(GetOwner());
		Parametri.bTraceComplex = true;

		bool colpito = GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, ECC_Visibility, Parametri);

		TSubclassOf<UDamageType> Danno;

		if (colpito)
		{
			UGameplayStatics::ApplyPointDamage(Hit.GetActor(), 10.f,Hit.ImpactNormal, Hit, GetOwner()->GetInstigatorController(), this, Danno);
			EndPoint = Hit.Location;
		}

		if (FrontFire)
		{
			UGameplayStatics::SpawnEmitterAttached(FrontFire, Weapon, TEXT("Muzzle"));
		}

		if (Scia)
		{
			auto PartPointer = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Scia, StartPoint);

			PartPointer->SetVectorParameter("BeamEnd", EndPoint);
		}

		Ammo -= 1;
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

