// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillArrowPlague.h"

#pragma region Unreal Engine functions
void ASkillArrowPlague::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 3;
	m_noiseValue = 1.0f;
}

void ASkillArrowPlague::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ASkillArrowPlague::OnActivationStart_Implementation()
{
}

void ASkillArrowPlague::OnActivationEnd_Implementation()
{
}
#pragma endregion
