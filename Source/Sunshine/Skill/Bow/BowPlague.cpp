// Fill out your copyright notice in the Description page of Project Settings.

#include "BowPlague.h"

#pragma region Unreal Engine functions
void ABowPlague::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 3;
	// Noise is made by the arrow not the bow
	m_noiseValue = 0.0f;
}

void ABowPlague::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ABowPlague::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	// Do something
}

void ABowPlague::OnActivationEnd_Implementation()
{
	// Do something

	Super::OnActivationEnd_Implementation();
}
#pragma endregion
