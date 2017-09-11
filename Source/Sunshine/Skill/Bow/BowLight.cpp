// Fill out your copyright notice in the Description page of Project Settings.

#include "BowLight.h"

#pragma region Unreal Engine functions
void ABowLight::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 2;
	m_noiseValue = 1.0f;
}

void ABowLight::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ABowLight::OnActivationStart_Implementation()
{
}

void ABowLight::OnActivationEnd_Implementation()
{
}
#pragma endregion