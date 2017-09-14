// Fill out your copyright notice in the Description page of Project Settings.

#include "LyrePlaying.h"

#pragma region Unreal Engine functions
void ALyrePlaying::BeginPlay()
{
	Super::BeginPlay();

	// Mana cost and noise depends on the song played
	m_manaCost = 0;
	m_noiseValue = 0.0f;
}

void ALyrePlaying::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ALyrePlaying::OnActivationStart_Implementation()
{
}

void ALyrePlaying::OnActivationEnd_Implementation()
{
}

void ALyrePlaying::OnFailedPlaying_Implementation()
{
	// Do something
}
#pragma endregion
