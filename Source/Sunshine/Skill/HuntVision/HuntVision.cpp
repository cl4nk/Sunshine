// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntVision.h"

#pragma region Unreal Engine functions
void AHuntVision::BeginPlay()
{
	Super::BeginPlay();
}

void AHuntVision::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	switch ( m_skillState )
	{
		case Waiting:
			TickWaiting();
			break;
		case StartHuntVision:
			TickStartHuntVision();
			break;
		case ActiveHuntVision:
			TickActiveHuntVision( deltaTime );
			break;
		case StopHuntVision:
			TickStopHuntVision();
			break;
	}
}
#pragma endregion

void AHuntVision::Init( ASunshineCharacter* owner )
{
	Super::Init( owner );

	// TODO: remove when used as blueprint
	m_manaCost = 1;
	m_noiseValue = 0.0f;

	m_skillState = Waiting;
}

#pragma region Events
void AHuntVision::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	if ( m_owner == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "Owner is nullptr !" ) );
		return;
	}

	if ( m_skillState != Waiting )
		return;

	m_skillState = StartHuntVision;
	SetActorTickEnabled( true );
}

void AHuntVision::OnActivationEnd_Implementation()
{
	// Do nothing

	Super::OnActivationEnd_Implementation();
}

void AHuntVision::TickWaiting()
{
	m_huntVisionTime = 0.0f;
	SetActorTickEnabled( false );
}

void AHuntVision::TickStartHuntVision()
{
	UE_LOG( LogTemp, Warning, TEXT( "Start hunt vision !" ) );

	// TODO: create function to do what the huntvision is supposed to do

	m_skillState = ActiveHuntVision;
}

void AHuntVision::TickActiveHuntVision( const float deltaTime )
{
	m_huntVisionTime += deltaTime;
	m_skillState = StopHuntVision;
}

void AHuntVision::TickStopHuntVision()
{
	// TODO: deactivate huntvision here

	m_huntVisionTime = 0.0f;
	m_skillState = Waiting;
	UE_LOG( LogTemp, Warning, TEXT( "Stop hunt vision !" ) );
}
#pragma endregion
