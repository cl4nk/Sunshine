// Fill out your copyright notice in the Description page of Project Settings.

#include "BowStandard.h"

#pragma region Unreal Engine functions
void ABowStandard::BeginPlay()
{
	Super::BeginPlay();

	// Does not cost mana nor make noise when shot
	m_manaCost = 0;
	m_noiseValue = 0.0f;
}

void ABowStandard::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ABowStandard::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	// Do something
}

void ABowStandard::OnActivationEnd_Implementation()
{
	// Do something

	Super::OnActivationEnd_Implementation();
}
#pragma endregion
