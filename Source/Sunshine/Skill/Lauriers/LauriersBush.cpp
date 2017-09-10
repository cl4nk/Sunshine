// Fill out your copyright notice in the Description page of Project Settings.

#include "LauriersBush.h"

#pragma region Unreal Engine functions
void ALauriersBush::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 2;
	m_noiseValue = 0.5f;
}

void ALauriersBush::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ALauriersBush::OnActivationStart_Implementation()
{
}

void ALauriersBush::OnActivationEnd_Implementation()
{
}
#pragma endregion