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
	RootComponent= Weapon;

	MaxAmmo = 30;
	Ammo = MaxAmmo;
	FireRate = 0.1f;
	Aggancio = false;
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
		FVector LocHit;
		FHitResult Hit;
		FVector StartPoint = Weapon->GetSocketLocation(TEXT("Muzzle"));
		bool colpito = AimingTrace(Hit,LocHit);
		//DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 1.f, 0, 1.f);
		
		TSubclassOf<UDamageType> Danno;

		if (colpito)
		{
			UGameplayStatics::ApplyPointDamage(Hit.GetActor(), 10.f,Hit.ImpactNormal, Hit, GetOwner()->GetInstigatorController(), this, Danno);
			LocHit = Hit.Location;
		}

		if (FrontFire)
		{
			UGameplayStatics::SpawnEmitterAttached(FrontFire, Weapon, TEXT("Muzzle"));
		}

		if (Scia)
		{
			auto PartPointer = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Scia, StartPoint);

			PartPointer->SetVectorParameter("BeamEnd", LocHit);
		}

		Ammo -= 1;
	}
}

bool AWeapon::AimingTrace(FHitResult &OutHit, FVector &HitLocation)
{
	FVector VistagiocatorePosizione;
	FRotator VistagiocatoreRotazione;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(VistagiocatorePosizione, VistagiocatoreRotazione);

	FCollisionQueryParams Parametri;

	Parametri.AddIgnoredActor(this);
	Parametri.AddIgnoredActor(GetOwner());
	Parametri.bTraceComplex = true;

	
    HitLocation = VistagiocatorePosizione + VistagiocatoreRotazione.Vector() * 5000.f;


	bool HitAim = GetWorld()->LineTraceSingleByChannel(OutHit, VistagiocatorePosizione,HitLocation, ECollisionChannel::ECC_Camera,Parametri);

	

	if (HitAim)
	{
		HitLocation = OutHit.ImpactPoint;
		if (Cast<APawn>(OutHit.Actor))
		{
			Aggancio = true;
			//DrawDebugLine(GetWorld(), VistagiocatorePosizione, End, FColor(255, 0, 0), false, 0.1f, 0, 1.f);
		}else
		{
			Aggancio = false;
			//DrawDebugLine(GetWorld(), VistagiocatorePosizione, End, FColor(0, 255, 0), false, 0.1f, 0, 1.f);
		}
	}
	return HitAim;
}



// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

