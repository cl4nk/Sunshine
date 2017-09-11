// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillArrowLight.h"

#pragma region Unreal Engine functions
void ASkillArrowLight::BeginPlay()
{
	Super::BeginPlay();

	m_manaCost = 2;
	m_noiseValue = 1.0f;
}

void ASkillArrowLight::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ASkillArrowLight::OnActivationStart_Implementation()
{
}

void ASkillArrowLight::OnActivationEnd_Implementation()
{
}
#pragma endregion
