// Fill out your copyright notice in the Description page of Project Settings.

#include "LauriersCreeper.h"

#pragma region Unreal Engine functions
void ALauriersCreeper::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 1;
	m_noiseValue = 0.5f;
}

void ALauriersCreeper::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ALauriersCreeper::OnActivationStart_Implementation()
{
}

void ALauriersCreeper::OnActivationEnd_Implementation()
{
}
#pragma endregion
