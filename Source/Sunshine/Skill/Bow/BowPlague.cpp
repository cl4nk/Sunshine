// Fill out your copyright notice in the Description page of Project Settings.

#include "BowPlague.h"

#pragma region Unreal Engine functions
void ABowPlague::BeginPlay()
{
	Super::BeginPlay();
}

void ABowPlague::Tick( float deltaTime )
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
		case BulletTime:
			TickBulletTime( deltaTime );
			break;
		case ShootBullet:
			TickShootBullet();
			break;
	}
}
#pragma endregion

void ABowPlague::Init( ASunshineCharacter* owner )
{
	Super::Init( owner );
	
	// TODO: remove when used as blueprint
	m_manaCost = 3;
	// Noise is made by the arrow not the bow
	m_noiseValue = 0.0f;

	m_skillState = Waiting;
}

#pragma region Events
void ABowPlague::OnActivationStart_Implementation()
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

void ABowPlague::OnActivationEnd_Implementation()
{
	if ( m_skillState != Waiting )
		m_skillState = ShootBullet;

	Super::OnActivationEnd_Implementation();
}

void ABowPlague::TickWaiting()
{
	m_bulletTime = 0.0f;
	SetActorTickEnabled( false );
}

void ABowPlague::TickStartBend()
{
	UE_LOG( LogTemp, Warning, TEXT( "TickStartBend()" ) );

	Bend();

	// TODO: activate bullettime
	m_skillState = BulletTime;
}

void ABowPlague::TickBulletTime( const float deltaTime )
{
	m_bulletTime += deltaTime;
	if ( m_bulletTime >= m_maxBulletTime )
		m_skillState = ShootBullet;
}

void ABowPlague::TickShootBullet()
{
	// TODO: stop bullettime
	UE_LOG( LogTemp, Warning, TEXT( "TickShootBullet()" ) );

	Shoot();

	m_bulletTime = 0.0f;
	m_skillState = Waiting;
	m_arrowInstance = nullptr;
}
#pragma endregion
