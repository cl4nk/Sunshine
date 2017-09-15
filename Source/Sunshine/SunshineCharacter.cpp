// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SunshineCharacter.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ASunshineCharacter

ASunshineCharacter::ASunshineCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ASunshineCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_currentMana = m_maxMana;

	TSubclassOf<ASkillBase> skillOne = m_defaultSkillOne;
	if ( skillOne == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "DefaultSkillOne is either null or not valid !" ) );
	}
	else
	{
		m_skillOne = skillOne.GetDefaultObject();
		m_skillOne->Init( this );
	}

	TSubclassOf<ASkillBase> skillTwo = m_defaultSkillTwo;
	if ( skillTwo == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "DefaultSkillTwo is either null or not valid !" ) );
	}
	else
	{
		m_skillTwo = skillTwo.GetDefaultObject();
		m_skillTwo->Init( this );
	}

	TSubclassOf<ASkillBase> skillUltimate = m_defaultSkillUltimate;
	if ( skillUltimate == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "DefaultSkillUltimate is either null or not valid !" ) );
	}
	else
	{	
		m_skillUltimate = skillUltimate.GetDefaultObject();
		m_skillUltimate->Init( this );
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASunshineCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASunshineCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASunshineCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASunshineCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASunshineCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ASunshineCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ASunshineCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ASunshineCharacter::OnResetVR);

	// Skills
	PlayerInputComponent->BindAction("SkillOne", IE_Pressed, this, &ASunshineCharacter::SkillOnePressed);
	PlayerInputComponent->BindAction("SkillOne", IE_Released, this, &ASunshineCharacter::SkillOneReleased);
	PlayerInputComponent->BindAction("SkillTwo", IE_Pressed, this, &ASunshineCharacter::SkillTwoPressed);
	PlayerInputComponent->BindAction("SkillTwo", IE_Released, this, &ASunshineCharacter::SkillTwoReleased);
	PlayerInputComponent->BindAction("SkillUltimate", IE_Pressed, this, &ASunshineCharacter::SkillUltimatePressed);
	PlayerInputComponent->BindAction("SkillUltimate", IE_Released, this, &ASunshineCharacter::SkillUltimateReleased);
}

bool ASunshineCharacter::IsHidden() const
{
	return m_hidingBushNum > 0;
}

void ASunshineCharacter::BeginHiding()
{
	++m_hidingBushNum;
}

void ASunshineCharacter::EndHiding()
{
	--m_hidingBushNum;
}

void ASunshineCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASunshineCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ASunshineCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ASunshineCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASunshineCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASunshineCharacter::Crouch()
{
	IsCrouching = true;
}

void ASunshineCharacter::StopCrouch()
{
	IsCrouching = false;
}

void ASunshineCharacter::Run()
{
	IsRunning = true;
}

void ASunshineCharacter::StopRun()
{
	IsRunning = false;
}

void ASunshineCharacter::Fall()
{
}

void ASunshineCharacter::MoveForward(float Value)
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

void ASunshineCharacter::MoveRight(float Value)
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

#pragma region Sun&Shine common Functions
void ASunshineCharacter::RangeWeaponPressed()
{
	m_bIsFocusing = true;
}

void ASunshineCharacter::RangeWeaponReleased()
{
	m_bIsFocusing = false;
}

void ASunshineCharacter::RangeWeapon()
{
}

void ASunshineCharacter::TakeCover()
{
}

void ASunshineCharacter::LeaveCover()
{
}

void ASunshineCharacter::SkillOnePressed()
{
	if ( m_skillOne == nullptr )
		return;

	StartSkill( m_skillOne );
}

void ASunshineCharacter::SkillOneReleased()
{
	if ( m_skillOne == nullptr )
		return;

	FinishSkill( m_skillOne );
}

void ASunshineCharacter::SkillTwoPressed()
{
	if ( m_skillTwo == nullptr )
		return;

	StartSkill( m_skillTwo );
}

void ASunshineCharacter::SkillTwoReleased()
{
	if ( m_skillTwo == nullptr )
		return;

	FinishSkill( m_skillTwo );
}

void ASunshineCharacter::SkillUltimatePressed()
{
	if ( m_skillUltimate == nullptr )
		return;

	StartSkill( m_skillUltimate );
}

void ASunshineCharacter::SkillUltimateReleased()
{
	if ( m_skillUltimate == nullptr )
		return;

	FinishSkill( m_skillUltimate );
}

void ASunshineCharacter::StartSkill( ASkillBase* skill )
{
	if ( m_bIsUsingSkill )
		return;

	m_bIsUsingSkill = true;

	skill->Start();
}

void ASunshineCharacter::FinishSkill( ASkillBase* skill )
{
	skill->Finish();

	m_bIsUsingSkill = false;
}
#pragma endregion
