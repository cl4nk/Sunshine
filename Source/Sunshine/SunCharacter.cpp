// Fill out your copyright notice in the Description page of Project Settings.

#include "SunCharacter.h"
#include "Skill/Bow/LightTeleport.h"
#include "Skill/Bow/LightZone.h"

void ASunCharacter::BeginPlay()
{
	Super::BeginPlay();

	CheckForLightSkill();
}

void ASunCharacter::ChangeMultiSkill( float rate )
{
	// TODO: change Arrow
}

ALightTeleport* ASunCharacter::GetLightTeleport() const
{
	switch ( m_idxLightSkill )
	{
		case 0:		return Cast<ALightTeleport>( m_skillOne );
		case 1:		return Cast<ALightTeleport>( m_skillTwo );
		case 2:		return Cast<ALightTeleport>( m_skillThree );
		default:	return nullptr;
	}
}

ALightZone* ASunCharacter::GetLightZone() const
{
	return m_lightZone;
}

bool ASunCharacter::EnterLightZone( ALightZone* lightTeleport )
{
	if ( m_lightZone )
		return false;

	m_lightZone = lightTeleport;
	return true;
}

bool ASunCharacter::LeaveLightZone( ALightZone* lightTeleport )
{
	if ( m_lightZone != lightTeleport )
		return false;

	m_lightZone = nullptr;
	return true;
}

bool ASunCharacter::IsInLightZone() const
{
	return m_lightZone != nullptr;
}

void ASunCharacter::CheckForLightSkill()
{
	if ( Cast<ALightTeleport>( m_skillOne ) )
		m_idxLightSkill = 0;
	else if ( Cast<ALightTeleport>( m_skillTwo ) )
		m_idxLightSkill = 1;
	else if ( Cast<ALightTeleport>( m_skillThree ) )
		m_idxLightSkill = 2;
	else
		UE_LOG( LogTemp, Error, TEXT("ASunCharacter::CheckForLightSkill() - could not find LightTeleport in skill list") );
}
