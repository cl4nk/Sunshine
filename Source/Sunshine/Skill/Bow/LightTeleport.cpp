// Fill out your copyright notice in the Description page of Project Settings.

#include "LightTeleport.h"

#pragma region Unreal Engine functions
void ALightTeleport::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 1;
	m_noiseValue = 0.0f;
}

void ALightTeleport::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ALightTeleport::OnActivationStart_Implementation()
{
}

void ALightTeleport::OnActivationEnd_Implementation()
{
}
#pragma endregion
