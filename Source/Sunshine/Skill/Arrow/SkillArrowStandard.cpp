// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillArrowStandard.h"

#pragma region Unreal Engine functions
void ASkillArrowStandard::BeginPlay()
{
	Super::BeginPlay();

	// Does not cost mana nor make noise when shot
	m_manaCost = 0;
	m_noiseValue = 0.0f;
}

void ASkillArrowStandard::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ASkillArrowStandard::OnActivationStart_Implementation()
{
}

void ASkillArrowStandard::OnActivationEnd_Implementation()
{
}
#pragma endregion
