// Fill out your copyright notice in the Description page of Project Settings.

#include "BowLight.h"

#pragma region Unreal Engine functions
void ABowLight::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 2;
	// Noise is made by the arrow not the bow
	m_noiseValue = 0.0f;
}

void ABowLight::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ABowLight::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	// Do something
}

void ABowLight::OnActivationEnd_Implementation()
{
	// Do something

	Super::OnActivationEnd_Implementation();
}
#pragma endregion
