// Fill out your copyright notice in the Description page of Project Settings.

#include "BowBase.h"

#pragma region Unreal Engine functions
void ABowBase::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 2;
	m_noiseValue = 1.0f;
}

void ABowBase::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ABowBase::OnActivationStart_Implementation()
{
}

void ABowBase::OnActivationEnd_Implementation()
{
}
#pragma endregion
