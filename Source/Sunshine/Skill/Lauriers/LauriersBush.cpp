// Fill out your copyright notice in the Description page of Project Settings.

#include "LauriersBush.h"
#include "Engine/World.h"
#include "SunshineCharacter.h"

#pragma region Unreal Engine functions
void ALauriersBush::BeginPlay()
{
	Super::BeginPlay();
}

void ALauriersBush::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}

void ALauriersBush::Init( ASunshineCharacter* character )
{
	Super::Init( character );

	m_manaCost = 2;
	m_noiseValue = 0.5f;
}
#pragma endregion

#pragma region Events
void ALauriersBush::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	if ( m_owner == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT("Owner is nullptr !") );
		return;
	}

	const FActorSpawnParameters spawnInfo;
	AActor* bush = GWorld->SpawnActor<AActor>(m_bushClass, m_owner->GetActorLocation(), m_owner->GetActorRotation(), spawnInfo);
	if (bush != nullptr)
	{
		UE_LOG( LogTemp, Warning, TEXT( "Actor has been spawned in the level" ) );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Failed to spawn actor!" ) );
	}
}

void ALauriersBush::OnActivationEnd_Implementation()
{
	// Do something

	Super::OnActivationEnd_Implementation();
}
#pragma endregion