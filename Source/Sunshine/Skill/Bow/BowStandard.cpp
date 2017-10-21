// Fill out your copyright notice in the Description page of Project Settings.

#include "BowStandard.h"

#pragma region Unreal Engine functions
void ABowStandard::BeginPlay()
{
	Super::BeginPlay();
}

void ABowStandard::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	switch ( m_skillState )
	{
		case Waiting:
			TickWaiting();
			break;
		case StartBend:
			TickStartBend();
			break;
		case IsArmed:
			TickIsArmed();
			break;
		case ShootArrow:
			TickShootArrow();
			break;
		case CancelShoot:
			TickCancelShoot();
			break;
		case PostAction:
			TickPostAction();
			break;
	}
}
#pragma endregion

void ABowStandard::Init( ASunshineCharacter* owner )
{
	Super::Init( owner );

	// TODO: remove when used as blueprint
	m_manaCost = 0;
	// Noise is made by the arrow not the bow
	m_noiseValue = 0.0f;

	m_skillState = Waiting;
}

void ABowStandard::ShootIfArmed()
{
	if ( m_skillState == IsArmed )
		m_skillState = ShootArrow;
}
#pragma region Events
void ABowStandard::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	if ( m_owner == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "Owner is nullptr !" ) );
		return;
	}

	if ( m_arrowInstance != nullptr )
		return;

	m_skillState = StartBend;
	SetActorTickEnabled( true );
}

void ABowStandard::OnActivationEnd_Implementation()
{
	if ( m_skillState != Waiting )
		m_skillState = CancelShoot;

	// TODO: ending animation probably here, need to check
	Super::OnActivationEnd_Implementation();
}

void ABowStandard::TickWaiting()
{
	SetActorTickEnabled( false );
}

void ABowStandard::TickStartBend()
{
	UE_LOG( LogTemp, Warning, TEXT( "TickStartBend()" ) );

	Bend();

	// TODO: activate bullettime
	m_skillState = IsArmed;
}

void ABowStandard::TickIsArmed()
{
	// Nothing to do
}

void ABowStandard::TickShootArrow()
{
	UE_LOG( LogTemp, Warning, TEXT( "TickShootArrow()" ) );

	Shoot();
	m_skillState = PostAction;
}

void ABowStandard::TickCancelShoot()
{
	UE_LOG( LogTemp, Warning, TEXT( "TickCancelShoot()" ) );

	Cancel();
	m_skillState = PostAction;
}

void ABowStandard::TickPostAction()
{
	m_skillState = Waiting;
	m_arrowInstance = nullptr;
}
#pragma endregion
