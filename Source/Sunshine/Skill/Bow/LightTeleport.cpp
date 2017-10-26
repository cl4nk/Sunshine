// Fill out your copyright notice in the Description page of Project Settings.

#include "LightTeleport.h"
#include "LightZone.h"
#include "SunCharacter.h"

#pragma region Unreal Engine functions
void ALightTeleport::BeginPlay()
{
	Super::BeginPlay();
}

void ALightTeleport::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	switch ( m_skillState )
	{
		case Waiting:
			TickWaiting();
			break;
		case Cooldown:
			TickCooldown( deltaTime );
			break;
	}
}
#pragma endregion

void ALightTeleport::Init( ASunshineCharacter* owner )
{
	Super::Init( owner );

	// TODO: remove when used as blueprint
	m_manaCost = 1;
	// Noise is made by the arrow not the bow
	m_noiseValue = 0.0f;

	m_skillState = Waiting;
}

bool ALightTeleport::ConsumeMana( int& characterMana ) const
{
	if ( !CanTeleport() )
		return false;

	return Super::ConsumeMana( characterMana );
}

void ALightTeleport::CreateNewLightZone( const FVector& worldLocation )
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.Owner = this;
	spawnInfo.Instigator = Instigator;

	ALightZone* newLightZone = GWorld->SpawnActor<ALightZone>( m_lightZoneClass, worldLocation,
	                                                           FRotator::ZeroRotator, spawnInfo );

	if ( m_bIsFirstZone )
	{
		if ( m_lightZoneOne )
			m_lightZoneOne->Destroy();
		m_lightZoneOne = newLightZone;
	}
	else
	{
		if ( m_lightZoneTwo )
			m_lightZoneTwo->Destroy();
		m_lightZoneTwo = newLightZone;
	}

	m_bIsFirstZone = !m_bIsFirstZone;
}

#pragma region Events
void ALightTeleport::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	if ( !CanTeleport() )
		return;

	TeleportCharacter();
	m_skillState = Cooldown;
	SetActorTickEnabled( true );
}

void ALightTeleport::OnActivationEnd_Implementation()
{
	// Do something

	Super::OnActivationEnd_Implementation();
}
#pragma endregion

bool ALightTeleport::CanTeleport() const
{
	ASunCharacter* sunCharacter = Cast<ASunCharacter>( m_owner );
	if ( !sunCharacter )
	{
		UE_LOG( LogTemp, Error, TEXT("ALightTeleport::CanTeleport() - owner is not ASunCharacter") );
		return false;
	}

	return m_skillState == Waiting
			&& m_lightZoneOne != nullptr
			&& m_lightZoneTwo != nullptr
			&& sunCharacter->IsInLightZone();
}

void ALightTeleport::TeleportCharacter() const
{
	// Already verified when calling this function
	ASunCharacter* sunCharacter = Cast<ASunCharacter>( m_owner );
	ALightZone* lightZone = sunCharacter->GetLightZone();

	if ( lightZone == m_lightZoneOne )
		Teleport( sunCharacter, m_lightZoneOne, m_lightZoneTwo );
	else if ( lightZone == m_lightZoneTwo )
		Teleport( sunCharacter, m_lightZoneTwo, m_lightZoneOne );
	else
		UE_LOG( LogTemp, Error, TEXT("ALightTeleport::TeleportCharacter() - SunCharacter's lightZone is not valid !") );
}

void ALightTeleport::Teleport( ASunCharacter* sunCharacter, ALightZone* start, ALightZone* destination ) const
{
	const FVector relativeLocation = sunCharacter->GetActorLocation() - start->GetActorLocation();
	sunCharacter->SetActorLocation( destination->GetActorLocation() + relativeLocation );
}

void ALightTeleport::TickWaiting()
{
	UE_LOG( LogTemp, Warning, TEXT("ALightTeleport::TickWaiting()") );

	m_cooldownSinceLastUse = 0.f;
	SetActorTickEnabled( false );
}

void ALightTeleport::TickCooldown( const float deltaTime )
{
	m_cooldownSinceLastUse += deltaTime;
	if ( m_cooldownSinceLastUse >= m_cooldownBetweenUse )
		m_skillState = Waiting;
}