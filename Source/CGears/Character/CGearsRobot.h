// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CGearsRobot.generated.h"

UCLASS(config=Game)
class ACGearsRobot : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* ShoulderBoom = nullptr;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera = nullptr;

	UPROPERTY(EditAnyWhere)
	TArray<USkeletalMesh*> BodyMeshes;

	UPROPERTY(EditAnyWhere)
	TArray<TSubclassOf<UAnimInstance>> AnimBP;

	UPROPERTY(VisibleAnyWhere, Category = "Mesh")
	USkeletalMeshComponent* Upper;

	UPROPERTY(VisibleAnyWhere, Category = "Mesh")
	USkeletalMeshComponent* Bottom;

	void StopAction();

public:
	ACGearsRobot();

	bool bAction;

	UPROPERTY(BlueprintReadOnly)
	float InputRight;

	UPROPERTY(BlueprintReadOnly)
	float InputForward;

	UPROPERTY(BlueprintReadOnly)
	bool  aim;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UHealthComponent* Vita;

	class AWeapon* SwitchGun(TArray <TSubclassOf<class AWeapon>> Type, AWeapon* pointer, int32& index, FName AttachPoint);

	void SwitchLeft();

	void SwitchRight();

	void InvokeSwitch();

	void Aiming();

	void MyJump();

	void StopAiming();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void Tick(float DeltaTime) override;

	void BeginPlay() override;

	void ChangeLegs();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
protected:

	UFUNCTION(BlueprintImplementableEvent)
	void CallWidget();

	AActor* CamNorm = nullptr;
	AActor* CamAim  = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor>GhostActor;

	UPROPERTY(EditAnywhere)
	TArray <TSubclassOf<class AWeapon>>WeaponTypeR;
	UPROPERTY(EditAnywhere)
	TArray <TSubclassOf<class AWeapon>>WeaponTypeL;

	UPROPERTY(BlueprintReadWrite)
	AWeapon* LeftArm;

	UPROPERTY(BlueprintReadWrite)
	AWeapon* RightArm;

	int32 RightWeapon;

	int32 LeftWeapon;

	void FireAction();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

};

