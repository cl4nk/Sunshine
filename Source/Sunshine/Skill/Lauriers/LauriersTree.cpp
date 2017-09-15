// Fill out your copyright notice in the Description page of Project Settings.

#include "LauriersTree.h"

#pragma region Unreal Engine functions
void ALauriersTree::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 3;
	m_noiseValue = 0.0f;
}

void ALauriersTree::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ALauriersTree::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	// Do something
}

void ALauriersTree::OnActivationEnd_Implementation()
{
	// Do something

	Super::OnActivationEnd_Implementation();
}
#pragma endregion
