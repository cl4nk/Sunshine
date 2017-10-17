// Fill out your copyright notice in the Description page of Project Settings.

#include "Bow.h"
#include "Engine/World.h"
#include "SunshineCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#pragma region Unreal Engine functions
void ABow::BeginPlay()
{
	Super::BeginPlay();
}

void ABow::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

void ABow::Init( ASunshineCharacter* owner )
{
	Super::Init( owner );

	m_manaCost = 0;
	m_noiseValue = 0.0f;
}

void ABow::Bend()
{
	m_owner->ChangeControllerMode( ESunshineCharacterControllerMode::Aiming );

	FActorSpawnParameters spawnInfo;
	spawnInfo.Owner = this;
	spawnInfo.Instigator = Instigator;

	// TODO: Spawn as child of the position of arrows of the m_owner
	m_arrowInstance = GWorld->SpawnActor<AArrow>( m_arrowType, m_owner->GetActorLocation(),
	                                              m_owner->GetActorRotation(),
	                                              spawnInfo );
	if ( m_arrowInstance != nullptr )
	{
		UE_LOG( LogTemp, Warning, TEXT( "Arrow has been instantiated !" ) );
		m_arrowInstance->AttachItemTo( m_owner->GetMesh(), FName( *m_owner->GetShootSocket() ) );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Failed to spawn actor!" ) );
	}
}

void ABow::Shoot()
{
	m_owner->ChangeControllerMode( ESunshineCharacterControllerMode::Normal );

	if ( m_arrowInstance )
	{
		UE_LOG( LogTemp, Warning, TEXT( "Shoot arrow !" ) );

		const FVector start = m_arrowInstance->GetActorLocation();
		const FVector end = GetAimedLocation();
		FVector direction = end - start;

		m_arrowInstance->DetachItem();
		m_arrowInstance->InitVelocity( direction.GetSafeNormal() );
	}
}

void ABow::Cancel()
{
	m_owner->ChangeControllerMode( ESunshineCharacterControllerMode::Normal );

	if (!m_arrowInstance)
		return;
	
	m_arrowInstance->DetachItem();
	m_arrowInstance->Destroy();
	UE_LOG( LogTemp, Warning, TEXT( "Cancel shoot !" ) );
}

FVector ABow::GetAimedLocation() const
{
	const FTransform cameraTransform = m_owner->GetFollowCamera()->GetComponentTransform();		
	const FVector lookLocation = cameraTransform.GetLocation();
	const FVector lookDirection = cameraTransform.GetRotation().GetForwardVector();

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor( m_owner );
	CollisionParams.bTraceComplex = true;
	CollisionParams.bReturnPhysicalMaterial = true;

	UWorld* world = GetWorld();
	check( world );

	FHitResult hitResult;
	if ( world->LineTraceSingleByChannel( hitResult, lookLocation, lookLocation + lookDirection * MaxAimedDistance, ECC_Visibility, CollisionParams ) )
	{
		return hitResult.ImpactPoint;
	}
	return lookLocation + lookDirection * MaxAimedDistance;
}
