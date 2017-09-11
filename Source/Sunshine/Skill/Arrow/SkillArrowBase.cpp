// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillArrowBase.h"

#pragma region Unreal Engine functions
void ASkillArrowBase::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 2;
	m_noiseValue = 1.0f;
}

void ASkillArrowBase::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ASkillArrowBase::OnActivationStart_Implementation()
{
}

void ASkillArrowBase::OnActivationEnd_Implementation()
{
}
#pragma endregion
