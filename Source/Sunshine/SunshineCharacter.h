// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SunshineCharacter.generated.h"

UCLASS(config=Game)
class ASunshineCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ASunshineCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate = 45.f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int MaxMana = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	float WalkSpeed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	float RunSpeed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Noise)
	float WalkNoise = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Noise)
	float RunNoise = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Noise)
	float CrouchNoise = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Noise)
	float JumpNoise = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Noise)
	float ClimbNoise = 0.5f;

protected:

	int CurrentMana = 0;

	bool IsRunning = false;

	bool IsCrouching = false;

	bool IsFocusing = false;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void Crouch();

	void StopCrouch();

	void Run();

	void StopRun();

	void Fall();

	void SkillSelection(float Value);

	void DistanceWeaponPressed();

	void DistanceWeaponReleased();

	virtual void LaunchDistanceWeapon();

	virtual void FirstSkill();

	virtual void SecondSkill();

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

