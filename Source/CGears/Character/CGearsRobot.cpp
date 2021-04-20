// Copyright Epic Games, Inc. All Rights Reserved.

#include "CGearsRobot.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "CGears/Weapons/Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "CGears/Componenti/HealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CGears/GameInstance_CGears.h"
#include "Kismet/GameplayStatics.h"
#include "CGears/CGearsGMPlay.h"

//////////////////////////////////////////////////////////////////////////
// ACGearsRobot

ACGearsRobot::ACGearsRobot()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	aim = false;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm	

	CameraSpalla = CreateDefaultSubobject<USceneComponent>(TEXT("Soggettiva"));
	CameraSpalla->SetupAttachment(GetCapsuleComponent());


	CameraNormal = CreateDefaultSubobject<USceneComponent>(TEXT("NormalView"));
	CameraNormal->SetupAttachment(CameraBoom);
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
    SpallaBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpallaBoom1"));
	SpallaBoom->SetupAttachment(CameraSpalla);
	SpallaBoom->TargetArmLength = 250.f;

	ActualWeapon = 0;

	Vita = CreateDefaultSubobject<UHealthComponent>(TEXT("Vita"));

}
//////////////////////////////////////////////////////////////////////////
// Input
void ACGearsRobot::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Switch", IE_Pressed, this, &ACGearsRobot::InvokeSwitch);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACGearsRobot::Aiming);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACGearsRobot::StopAiming);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACGearsRobot::FireAction);
	PlayerInputComponent->BindAction("SwitchGun", IE_Pressed, this, &ACGearsRobot::SwitchGun);


	PlayerInputComponent->BindAxis("MoveForward", this, &ACGearsRobot::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACGearsRobot::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACGearsRobot::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACGearsRobot::LookUpAtRate);

}

void ACGearsRobot::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACGearsRobot::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACGearsRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (aim)
	{
		FHitResult OutHit;
		FVector LocHit;
		float temp = GetControlRotation().Pitch;
		CameraSpalla->SetRelativeRotation(FRotator(temp,0,0));
		CurrentWeapon->AimingTrace(OutHit, LocHit);
	}
}

void ACGearsRobot::BeginPlay()
{
	 Super::BeginPlay();
	 

	 CamNorm = GetWorld()->SpawnActor<AActor>(GhostActor);
	 CamNorm->AttachToComponent(CameraNormal,FAttachmentTransformRules::SnapToTargetNotIncludingScale,NAME_None);

	 CamAim = GetWorld()->SpawnActor<AActor>(GhostActor);
	 CamAim->AttachToComponent(SpallaBoom, FAttachmentTransformRules::SnapToTargetNotIncludingScale,NAME_None);

	 SwitchGun();
	 
}

void ACGearsRobot::SwitchGun()
{

	if (CurrentWeapon)
	{
		UGameInstance_CGears* GI = Cast<UGameInstance_CGears>(UGameplayStatics::GetGameInstance(GetWorld()));
		for (int i = GI->Ammo.Num(); i < WeaponType.Num(); i++)
		{
			GI->Ammo.Add(-1);
		}

		GI->Ammo[ActualWeapon] = CurrentWeapon->GetAmmo();
		CurrentWeapon->Destroy();
		if (ActualWeapon < WeaponType.Num()-1)
		{
			ActualWeapon++;
		}
		else {
			ActualWeapon = 0;
		}

		CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponType[ActualWeapon]);
		if(GI->Ammo[ActualWeapon]!=-1)CurrentWeapon->SetAmmo(GI->Ammo[ActualWeapon]);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("GripWeapon"));
		CurrentWeapon->SetOwner(this);
		CallWidget();

	}
	else {


		CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponType[ActualWeapon]);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("GripWeapon"));
		CurrentWeapon->SetOwner(this);
		CallWidget();
	}



}



void ACGearsRobot::FireAction()
{
	CurrentWeapon->Fire();
}

void ACGearsRobot::InvokeSwitch()
{
	auto gm = GetWorld()->GetAuthGameMode();
	auto myGM = Cast<ACGearsGMPlay>(gm);
	if (myGM) 
	{ 
		myGM->SwitchTarget(); 
	}
}

void ACGearsRobot::Aiming()
{
		aim = true;
		// set our turn rates for input
		BaseTurnRate = 45.f;
		BaseLookUpRate = 45.f;

		// Don't rotate when the controller rotates. Let that just affect the camera.
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = true;
		bUseControllerRotationRoll = false;

		// Configure character movement
		GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
		GetCharacterMovement()->MaxWalkSpeed = 300;
		// Create a camera boom (pulls in towards the player if there is a collision)

		auto MC = Cast<APlayerController>(GetController());

		CameraBoom->Deactivate();
		SpallaBoom->Activate();

		MC->SetViewTargetWithBlend(CamAim, 0.25f, EViewTargetBlendFunction::VTBlend_EaseInOut, 1.f, true);
		
		CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

		FollowCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

}

void ACGearsRobot::StopAiming()
{
	aim = false;
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 600;

	auto MC = Cast<APlayerController>(GetController());

	MC->SetViewTargetWithBlend(CamNorm, 0.25f, EViewTargetBlendFunction::VTBlend_EaseInOut, 1.f, true);

	// The camera follows at this distance behind the character	
	SpallaBoom->Deactivate();
	CameraBoom->Activate();
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void ACGearsRobot::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACGearsRobot::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
