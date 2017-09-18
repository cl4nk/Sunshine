// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Skill/SkillBase.h"
#include "SunshineCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnAction );

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPawnNoiseEmitterComponent* NoiseEmitter;

public:
	ASunshineCharacter();	

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate = 45.f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate = 45.f;

	/**
	 * \brief Event called when the character moves after an input
	 */
	UPROPERTY(BlueprintAssignable)
	FOnAction OnInputMovement;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Category = "CharacterMovement", VisibleAnywhere, BlueprintReadOnly)
	bool JogPressed = false;

	UPROPERTY(Category = "CharacterMovement", VisibleAnywhere, BlueprintReadOnly)
	bool CrouchPressed = false;

	UPROPERTY(Category = "CharacterMovement", VisibleAnywhere, BlueprintReadOnly)
	bool JumpPressed = false;

	UPROPERTY(Category = "CharacterMovement", VisibleAnywhere, BlueprintReadOnly)
	bool DisableMovement = false;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward( float Value );

	/** Called for side to side input */
	void MoveRight( float Value );

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate( float Rate );

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate( float Rate );
	
	void OnJogPressed();
	
	void OnJogReleased();
	
	void OnJumpPressed();
	
	void OnJumpReleased();
	
	void OnCrouchPressed();
	
	void OnCrouchReleased();

	void Run();

	void StopRun();

	void Fall();

	/** Handler for when a touch input begins. */
	void TouchStarted( ETouchIndex::Type FingerIndex, FVector Location );

	/** Handler for when a touch input stops. */
	void TouchStopped( ETouchIndex::Type FingerIndex, FVector Location );

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
	// End of APawn interface

public:
	UFUNCTION( BlueprintCallable, Category = "Infiltration System")
	bool IsHidden() const;

	UFUNCTION( BlueprintCallable, Category = "Infiltration System")
	void BeginHiding();

	UFUNCTION( BlueprintCallable, Category = "Infiltration System")
	void EndHiding();

	UFUNCTION(BlueprintCallable, Category = "Infiltration System")
	void EmitWalkNoise();

	UFUNCTION(BlueprintCallable, Category = "Infiltration System")
	void EmitRunNoise();

	UFUNCTION(BlueprintCallable, Category = "Infiltration System")
	void EmitJumpStartNoise();

	UFUNCTION(BlueprintCallable, Category = "Infiltration System")
	void EmitJumpEndNoise();

	UFUNCTION(BlueprintCallable, Category = "Infiltration System")
	void EmitCrouchNoise();

	UFUNCTION(BlueprintCallable, Category = "Infiltration System")
	void EmitNoise(const float &Loudness);

private:
	/**
	 * \brief Tells wether the character is hidden 
	 */
	uint16_t m_hidingBushNum = 0;

#pragma region Sun&Shine common Stats
protected:
	// TODO: Every Stat should be changed to "EditDefaultsOnly" with "VisibleAnywhere" after debug
#pragma region Mana
	/**
	 * \brief Maximum mana of the Character
	 */
	UPROPERTY(Category = "Stats|Mana", EditAnywhere, BlueprintReadOnly)
	int m_maxMana = 10;

	/**
	 * \brief Current mana of the Character
	 */
	UPROPERTY(Category = "Stats|Mana", VisibleAnywhere, BlueprintReadOnly)
	int m_currentMana = 0;
#pragma endregion

#pragma region Walk
	/**
	 * \brief Walk speed of the Character
	 */
	UPROPERTY(Category = "Stats|Walk", EditAnywhere, BlueprintReadOnly)
	float m_walkSpeed = 200.0f;

	/**
	 * \brief Noise produced by the Character when walking
	 */
	UPROPERTY(Category = "Stats|Walk", EditAnywhere, BlueprintReadOnly)
	float m_walkNoise = 1.f;
#pragma endregion

#pragma region Run
	/**
	 * \brief Run speed of the Character
	 */
	UPROPERTY(Category = "Stats|Run", EditAnywhere, BlueprintReadOnly)
	float m_runSpeed = 675.0f;

	/**
	 * \brief Noise produced by the Character when running
	 */
	UPROPERTY(Category = "Stats|Run", EditAnywhere, BlueprintReadOnly)
	float m_runNoise = 2.f;
#pragma endregion

#pragma region Crouch
	/**
	 * \brief Crouch speed of the Character
	 */
	UPROPERTY(Category = "Stats|Crouch", EditAnywhere, BlueprintReadOnly)
	float m_crouchSpeed = 160.0f;

	/**
	 * \brief Noise produced by the Character when crouching
	 */
	UPROPERTY(Category = "Stats|Crouch", EditAnywhere, BlueprintReadOnly)
	float m_crouchNoise = 0.f;
#pragma endregion

#pragma region Climb
	/**
	 * \brief Climb speed of the Character
	 */
	UPROPERTY(Category = "Stats|Climb", EditAnywhere, BlueprintReadOnly)
	float m_climbSpeed = 150.0f;

	/**
	 * \brief Noise produced by the Character when climbing
	 */
	UPROPERTY(Category = "Stats|Climb", EditAnywhere, BlueprintReadOnly)
	float m_climbNoise = 0.5f;
#pragma endregion

	/**
	 * \brief Noise produced by the Character when jumping
	 */
	UPROPERTY(Category = "Stats|Jump", EditAnywhere, BlueprintReadOnly)
	float m_jumpNoise = 2.f;

	// TODO: projectile to be set
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	// Projectile* m_weapon = nullptr;
#pragma endregion

#pragma region Sun&Shine common Functions
protected:
#pragma region Skills
	// Change from UClass to TSubClassOf<ASkillBase>
	#pragma region Skill One
	UPROPERTY(Category = "Skills", EditDefaultsOnly, BlueprintReadWrite)
	UClass*	m_defaultSkillOne = nullptr;

	/**
	 * \brief First skill of the character
	 */
	UPROPERTY(Category = "Skills", VisibleAnywhere, BlueprintReadWrite)
	ASkillBase* m_skillOne = nullptr;

	/**
	 * \brief Try to execute skill one
	 */
	void SkillOnePressed();

	/**
	 * \brief Try to end skill one execution
	 */
	void SkillOneReleased();
	#pragma endregion

	#pragma region Skill Two
	UPROPERTY(Category = "Skills", EditDefaultsOnly, BlueprintReadWrite)
	UClass*	m_defaultSkillTwo = nullptr;

	/**
	 * \brief Second skill of the character
	 */
	UPROPERTY(Category = "Skills", VisibleAnywhere, BlueprintReadWrite)
	ASkillBase* m_skillTwo = nullptr;

	/**
	 * \brief Try to execute skill two
	 */
	void SkillTwoPressed();

	/**
	 * \brief Try to end skill one execution
	 */
	void SkillTwoReleased();
	#pragma endregion
	
	#pragma region Skill Three
	UPROPERTY(Category = "Skills", EditDefaultsOnly, BlueprintReadWrite)
	UClass*	m_defaultSkillThree = nullptr;

	/**
	 * \brief Third skill of the character
	 */
	UPROPERTY(Category = "Skills", VisibleAnywhere, BlueprintReadWrite)
	ASkillBase* m_skillThree = nullptr;

	/**
	 * \brief Try to execute skill three
	 */
	void SkillThreePressed();

	/**
	 * \brief Try to end skill one execution
	 */
	void SkillThreeReleased();
	#pragma endregion
	
	#pragma region Skill Four
	UPROPERTY(Category = "Skills", EditDefaultsOnly, BlueprintReadWrite)
	UClass*	m_defaultSkillFour = nullptr;

	/**
	 * \brief Fourth skill of the character
	 */
	UPROPERTY(Category = "Skills", VisibleAnywhere, BlueprintReadWrite)
	ASkillBase* m_skillFour = nullptr;

	/**
	 * \brief Try to execute skill four
	 */
	void SkillFourPressed();

	/**
	 * \brief Try to end skill one execution
	 */
	void SkillFourReleased();
	#pragma endregion

	/**
	 * \brief Is a skill being used or not
	 */
	UPROPERTY(Category = "Skills", VisibleAnywhere, BlueprintReadOnly)
	bool m_bIsUsingSkill = false;
	
	UPROPERTY(Category = "Skills", VisibleAnywhere, BlueprintReadOnly)
	int m_skillUsed = -1;

	/**
	 * \brief Starts the skill
	 * \param skill _IN_ The skill to call Start() on
	 */
	void StartSkill( ASkillBase* skill, int index );

	/**
	 * \brief Finishes the skill
	 * \param skill _IN_ The skill to call Finish() on
	 */
	void FinishSkill( ASkillBase* skill );
#pragma endregion

private:

	/**
	 * \brief Called when taking cover
	 */
	void TakeCover();

	/**
	 * \brief Called when leaving cover
	 */
	void LeaveCover();
#pragma endregion

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns NoiseEmitter subobject **/
	FORCEINLINE class UPawnNoiseEmitterComponent* GetNoiseEmitter() const { return NoiseEmitter; }
};
