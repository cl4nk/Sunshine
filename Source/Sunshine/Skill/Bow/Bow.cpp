// Fill out your copyright notice in the Description page of Project Settings.

#include "Bow.h"
#include "Engine/World.h"
#include "SunshineCharacter.h"

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
		m_arrowInstance->AttachItemTo(m_owner->GetMesh(), FName(*m_owner->GetShootSocket()));
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Failed to spawn actor!" ) );
	}
}

void ABow::Shoot()
{
	if ( m_arrowInstance )
	{
		UE_LOG( LogTemp, Warning, TEXT( "Shoot arrow !" ) );

		const FVector launchDir = m_arrowInstance->GetActorRotation().Vector();
		m_arrowInstance->InitVelocity( launchDir );
		m_arrowInstance->DetachItem();
	}
}

void ABow::Cancel()
{
	m_arrowInstance->Destroy();
	UE_LOG( LogTemp, Warning, TEXT( "Cancel shoot !" ) );
}
