// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillBase.h"

ASkillBase::ASkillBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

#pragma region Unreal Engine functions
void ASkillBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASkillBase::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}
#pragma endregion

#pragma region Events
void ASkillBase::OnActivationStart_Implementation()
{
}

void ASkillBase::OnActivationEnd_Implementation()
{
}
#pragma endregion

#pragma region Getters
uint32_t ASkillBase::GetManaCost() const
{
	return m_manaCost;
}

float ASkillBase::GetNoiseValue() const
{
	return m_noiseValue;
}
#pragma endregion
