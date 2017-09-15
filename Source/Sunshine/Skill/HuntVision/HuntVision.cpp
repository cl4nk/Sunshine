// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntVision.h"

#pragma region Unreal Engine functions
void AHuntVision::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 1;
	m_noiseValue = 0.0f;
}

void AHuntVision::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void AHuntVision::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	// Do something
}

void AHuntVision::OnActivationEnd_Implementation()
{
	// Do something

	Super::OnActivationEnd_Implementation();
}
#pragma endregion
