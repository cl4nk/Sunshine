// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillBase.h"

ASkillBase::ASkillBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
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
	m_bIsActive = true;
}

void ASkillBase::OnActivationEnd_Implementation()
{
	m_bIsActive = false;
}
#pragma endregion

#pragma region Getters
int ASkillBase::GetManaCost() const
{
	return m_manaCost;
}

float ASkillBase::GetNoiseValue() const
{
	return m_noiseValue;
}

void ASkillBase::Init( ASunshineCharacter* owner )
{
	m_owner = owner;
}

void ASkillBase::Start()
{
	if ( m_bIsActive )
		return;

	OnActivationStart();
}

void ASkillBase::Finish()
{
	if ( !m_bIsActive )
		return;

	OnActivationEnd();
}
#pragma endregion
