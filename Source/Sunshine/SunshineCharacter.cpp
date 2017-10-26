// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SunshineCharacter.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Skill/Weapon.h"

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
	
	//Enable the crouch functionality
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	
	GetCharacterMovement()->MaxWalkSpeed = m_walkSpeed;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ASunshineCharacter::BeginPlay()
{
	Super::BeginPlay();

	if ( CameraBoom && FollowCamera )
	{
		CameraBaseDistance = CameraBoom->TargetArmLength;
		CameraBaseOffset = CameraBoom->SocketOffset;
		CameraBaseFOV = FollowCamera->FieldOfView;

		CameraTargetDistance = CameraBaseDistance;
		CameraTargetOffset = CameraBaseOffset;
		CameraTargetFOV = CameraBaseFOV;
	}
	else
		UE_LOG( LogTemp, Error, TEXT("ASunshineCharacter::BeginPlay() - CameraBoom and/or FollowCamera is nullptr") );

	//ChangeControllerMode( ESunshineCharacterControllerMode::Normal );

	m_currentMana = m_maxMana;

	if ( m_defaultSkillOne == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "DefaultSkillOne is either null or not valid !" ) );
	}
	else
	{
		m_skillOne = GWorld->SpawnActor<ASkillBase>(m_defaultSkillOne);
		m_skillOne->Init( this );
	}

	if ( m_defaultSkillTwo == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "DefaultSkillTwo is either null or not valid !" ) );
	}
	else
	{
		m_skillTwo = GWorld->SpawnActor<ASkillBase>(m_defaultSkillTwo);
		m_skillTwo->Init( this );
	}
	
	if ( m_defaultSkillThree == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "DefaultSkillThree is either null or not valid !" ) );
	}
	else
	{
		m_skillThree = GWorld->SpawnActor<ASkillBase>(m_defaultSkillThree);
		m_skillThree->Init( this );
	}
	
	if ( m_defaultSkillWeapon == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "DefaultSkillFour is either null or not valid !" ) );
	}
	else
	{
		m_skillWeapon = GWorld->SpawnActor<ASkillBase>(m_defaultSkillWeapon);
		m_skillWeapon->Init( this );

		if ( Cast<IWeapon>( m_skillWeapon ) == nullptr )
			UE_LOG( LogTemp, Error, TEXT( "Skill Four/Weapon is not inheriting from IWeapon" ) );
	}

}

void ASunshineCharacter::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	TickUpdateCamera( deltaTime );
}

#pragma region Camera
void ASunshineCharacter::TickUpdateCamera( const float deltaTime ) const
{
	if ( CameraBoom && CameraBoom->TargetArmLength != CameraTargetDistance )
	{
		CameraBoom->TargetArmLength = FMath::Lerp( CameraBoom->TargetArmLength, CameraTargetDistance, deltaTime );
	}
	if ( CameraBoom && CameraBoom->SocketOffset != CameraTargetOffset )
	{
		CameraBoom->SocketOffset = FMath::Lerp( CameraBoom->SocketOffset, CameraTargetOffset, deltaTime );
	}
	if ( FollowCamera && FollowCamera->FieldOfView != CameraTargetFOV )
	{
		FollowCamera->FieldOfView = FMath::Lerp( FollowCamera->FieldOfView, CameraTargetFOV, deltaTime );
	}
}

void ASunshineCharacter::ChangeControllerMode( const ESunshineCharacterControllerMode newCameraMode )
{
	switch ( newCameraMode )
	{
		case ESunshineCharacterControllerMode::Normal:
		{
			CameraTargetDistance = CameraBaseDistance;
			CameraTargetOffset = CameraBaseOffset;
			CameraTargetFOV = CameraBaseFOV;

			GetCharacterMovement()->bOrientRotationToMovement = true;
			bUseControllerRotationYaw = false;

			break;
		}
		case ESunshineCharacterControllerMode::Aiming:
		{
			CameraTargetDistance = CameraAimDistance;
			CameraTargetOffset = CameraAimOffset;
			CameraTargetFOV = CameraAimFOV;

			GetCharacterMovement()->bOrientRotationToMovement = false;
			bUseControllerRotationYaw = true;
			
			// TODO: Try to lerp this, no tp
			SetActorRotation( GetCameraBoom()->GetComponentRotation() );
			break;
		}
		case ESunshineCharacterControllerMode::Unknown:
		default:
			break;
	}
}
#pragma endregion

//////////////////////////////////////////////////////////////////////////
// Input

void ASunshineCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction( "Jump", IE_Pressed, this, &ASunshineCharacter::OnJumpPressed );
	PlayerInputComponent->BindAction( "Jump", IE_Released, this, &ASunshineCharacter::OnJumpReleased );

	PlayerInputComponent->BindAction( "Crouch", IE_Pressed, this, &ASunshineCharacter::OnCrouchPressed );
	PlayerInputComponent->BindAction( "Crouch", IE_Released, this, &ASunshineCharacter::OnCrouchReleased );

	PlayerInputComponent->BindAction( "Jog", IE_Pressed, this, &ASunshineCharacter::OnJogPressed );
	PlayerInputComponent->BindAction( "Jog", IE_Released, this, &ASunshineCharacter::OnJogReleased );

	PlayerInputComponent->BindAxis( "MoveForward", this, &ASunshineCharacter::MoveForward );
	PlayerInputComponent->BindAxis( "MoveRight", this, &ASunshineCharacter::MoveRight );

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis( "Turn", this, &APawn::AddControllerYawInput );
	PlayerInputComponent->BindAxis( "TurnRate", this, &ASunshineCharacter::TurnAtRate );
	PlayerInputComponent->BindAxis( "LookUp", this, &APawn::AddControllerPitchInput );
	PlayerInputComponent->BindAxis( "LookUpRate", this, &ASunshineCharacter::LookUpAtRate );

	// handle touch devices
	PlayerInputComponent->BindTouch( IE_Pressed, this, &ASunshineCharacter::TouchStarted );
	PlayerInputComponent->BindTouch( IE_Released, this, &ASunshineCharacter::TouchStopped );

	// VR headset functionality
	PlayerInputComponent->BindAction( "ResetVR", IE_Pressed, this, &ASunshineCharacter::OnResetVR );

	// Skills
	PlayerInputComponent->BindAction( "SkillOne", IE_Pressed, this, &ASunshineCharacter::SkillOnePressed );
	PlayerInputComponent->BindAction( "SkillOne", IE_Released, this, &ASunshineCharacter::SkillOneReleased );
	PlayerInputComponent->BindAction( "SkillTwo", IE_Pressed, this, &ASunshineCharacter::SkillTwoPressed );
	PlayerInputComponent->BindAction( "SkillTwo", IE_Released, this, &ASunshineCharacter::SkillTwoReleased );
	PlayerInputComponent->BindAction( "SkillThree", IE_Pressed, this, &ASunshineCharacter::SkillThreePressed );
	PlayerInputComponent->BindAction( "SkillThree", IE_Released, this, &ASunshineCharacter::SkillThreeReleased );
	PlayerInputComponent->BindAxis( "MultiSkill", this, &ASunshineCharacter::ChangeMultiSkill );

	PlayerInputComponent->BindAction( "AimWeapon", IE_Pressed, this, &ASunshineCharacter::SkillWeaponPressed );
	PlayerInputComponent->BindAction( "AimWeapon", IE_Released, this, &ASunshineCharacter::SkillWeaponReleased );
	PlayerInputComponent->BindAction( "ShootWeapon", IE_Pressed, this, &ASunshineCharacter::SkillShoot );
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

void ASunshineCharacter::EmitWalkNoise()
{
	NoiseEmitter->MakeNoise(this, m_walkNoise, GetActorLocation());
}

void ASunshineCharacter::EmitRunNoise()
{
	NoiseEmitter->MakeNoise(this, m_runNoise, GetActorLocation());
}

void ASunshineCharacter::EmitJumpStartNoise()
{
	NoiseEmitter->MakeNoise(this, m_jumpNoise, GetActorLocation());
}

void ASunshineCharacter::EmitJumpEndNoise()
{
	NoiseEmitter->MakeNoise(this, m_jumpNoise, GetActorLocation());
}

void ASunshineCharacter::EmitCrouchNoise()
{
	NoiseEmitter->MakeNoise(this, m_crouchNoise, GetActorLocation());
}

void ASunshineCharacter::EmitNoise(const float &Loudness)
{
	NoiseEmitter->MakeNoise(this, Loudness, GetActorLocation());
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

void ASunshineCharacter::Fall()
{
}

void ASunshineCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		OnInputMovement.Broadcast();

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
		OnInputMovement.Broadcast();
		
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ASunshineCharacter::OnJogPressed()
{
	JogPressed = true;
	UpdateWalkSpeed();
}

void ASunshineCharacter::OnJogReleased()
{
	JogPressed = false;
	UpdateWalkSpeed();
}

void ASunshineCharacter::OnJumpPressed()
{
	JumpPressed = true;
	Jump();
}

void ASunshineCharacter::OnJumpReleased()
{
	JumpPressed = false;
	StopJumping();
}

void ASunshineCharacter::OnCrouchPressed()
{
	CrouchPressed = true;
	Crouch();
	UpdateWalkSpeed();
}

void ASunshineCharacter::OnCrouchReleased()
{
	CrouchPressed = false;
	UnCrouch();
	UpdateWalkSpeed();
}

void ASunshineCharacter::UpdateWalkSpeed()
{
	if (CrouchPressed)
		GetCharacterMovement()->MaxWalkSpeed = m_crouchSpeed;
	else if (m_bIsUsingSkill)
		GetCharacterMovement()->MaxWalkSpeed = m_walkSpeed;
	else if (JogPressed)
		GetCharacterMovement()->MaxWalkSpeed = m_runSpeed;
	else 
		GetCharacterMovement()->MaxWalkSpeed = m_walkSpeed;
}

#pragma region Sun&Shine common Functions
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

	StartSkill( m_skillOne, 0 );
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

	StartSkill( m_skillTwo, 1 );
}

void ASunshineCharacter::SkillTwoReleased()
{
	if ( m_skillTwo == nullptr )
		return;

	FinishSkill( m_skillTwo );
}

void ASunshineCharacter::SkillThreePressed()
{
	if ( m_skillThree == nullptr )
		return;

	StartSkill( m_skillThree, 2 );
}

void ASunshineCharacter::SkillThreeReleased()
{
	if ( m_skillThree == nullptr )
		return;

	FinishSkill( m_skillThree );
}

void ASunshineCharacter::SkillWeaponPressed()
{
	if ( m_skillWeapon == nullptr )
		return;

	StartSkill( m_skillWeapon, 3 );
}

void ASunshineCharacter::SkillWeaponReleased()
{
	if ( m_skillWeapon == nullptr )
		return;

	FinishSkill( m_skillWeapon );
}

void ASunshineCharacter::SkillShoot()
{
	if ( m_bIsUsingSkill && m_skillUsed == 3 )
	{
		Cast<IWeapon>( m_skillWeapon )->ShootIfArmed();
	}
}

void ASunshineCharacter::ChangeMultiSkill( float rate )
{
	// To be overriden
}

void ASunshineCharacter::StartSkill( ASkillBase* skill, const int index )
{
	if ( m_bIsUsingSkill )
		return;

	if ( !skill->ConsumeMana( m_currentMana ) )
		return;

	m_bIsUsingSkill = true;
	m_skillUsed = index;

	skill->Start();
	
	GetCharacterMovement()->MaxWalkSpeed = m_walkSpeed;
}

void ASunshineCharacter::FinishSkill( ASkillBase* skill )
{
	skill->Finish();

	m_skillUsed = -1;
	m_bIsUsingSkill = false;
	
	UpdateWalkSpeed();
}

ASkillBase*	ASunshineCharacter::GetSkill (const int index) const
{
	switch (index)
	{
		case 0 : return m_skillOne;
		case 1 : return m_skillTwo;
		case 2 : return m_skillThree;
		case 3 : return m_skillWeapon;
		default: return nullptr;
	}
}
#pragma endregion
