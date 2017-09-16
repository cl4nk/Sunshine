// Fill out your copyright notice in the Description page of Project Settings.

#include "LauriersTree.h"
#include "SunshineCharacter.h"

#pragma region Unreal Engine functions
void ALauriersTree::BeginPlay()
{
	Super::BeginPlay();
}

void ALauriersTree::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	switch ( m_skillState )
	{
		case Waiting:
			TickWaiting();
			break;
		case StartTransformation:
			TickStartTransformation();
			break;
		case IsTransformed:
			TickIsTransformed( deltaTime );
			break;
		case StopTransformation:
			TickStopTransformation();
			break;
	}
}

void ALauriersTree::Init( ASunshineCharacter* owner )
{
	Super::Init( owner );

	// TODO: remove when used as blueprint
	m_manaCost = 3;
	m_noiseValue = 0.0f;

	m_skillState = Waiting;
}
#pragma endregion

#pragma region Events
void ALauriersTree::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	if ( m_owner == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "Owner is nullptr !" ) );
		return;
	}

	if ( m_skillState != Waiting )
		return;

	m_skillState = StartTransformation;
	SetActorTickEnabled( true );
}

void ALauriersTree::OnActivationEnd_Implementation()
{
	// Do nothing

	Super::OnActivationEnd_Implementation();
}

void ALauriersTree::CancelTransform()
{
	m_skillState = StopTransformation;
}

void ALauriersTree::TickWaiting()
{
	m_transformationTime = 0.0f;
	SetActorTickEnabled( false );
}

void ALauriersTree::TickStartTransformation()
{
	UE_LOG( LogTemp, Warning, TEXT( "Start transformation !" ) );
	m_owner->OnInputMovement.AddDynamic( this, &ALauriersTree::CancelTransform );
	m_owner->SetActorHiddenInGame( true );

	const FActorSpawnParameters spawnInfo;
	m_treeInstance = GWorld->SpawnActor<AActor>( m_treeClass, m_owner->GetActorLocation(), m_owner->GetActorRotation(),
	                                             spawnInfo );
	if ( m_treeInstance != nullptr )
	{
		UE_LOG( LogTemp, Warning, TEXT( "Has been transformed !" ) );
		m_skillState = IsTransformed;
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Failed to spawn actor!" ) );
		m_skillState = StopTransformation;
	}
}

void ALauriersTree::TickIsTransformed( const float deltaTime )
{
	m_transformationTime += deltaTime;
	if ( m_transformationTime >= m_maxTransformationTime )
		CancelTransform();
}

void ALauriersTree::TickStopTransformation()
{
	m_treeInstance->Destroy();
	m_owner->SetActorHiddenInGame( false );

	m_transformationTime = 0.0f;
	m_owner->OnInputMovement.RemoveDynamic( this, &ALauriersTree::CancelTransform );
	m_skillState = Waiting;
	UE_LOG( LogTemp, Warning, TEXT( "Stop transformation !" ) );
}
#pragma endregion
