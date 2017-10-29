// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SunshineCharacter.h"

class ALightZone;
class ALightTeleport;

#include "SunCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SUNSHINE_API ASunCharacter : public ASunshineCharacter
{
	GENERATED_BODY()

public:
	virtual ~ASunCharacter() = default;

protected:
	virtual void BeginPlay() override;

public:
	virtual void ChangeMultiSkill( float rate ) override;

	/**
	 * \brief Gets the LightTeleport skill
	 * \return The LightTeleport skill if exists, nullptr otherwise
	 */
	UFUNCTION( Category = "SunshineCharacter|SunCharacter|LightTeleport", BlueprintCallable )
	ALightTeleport* GetLightTeleport() const;

	UFUNCTION( Category = "SunshineCharacter|SunCharacter|LightTeleport", BlueprintCallable )
	ALightZone* GetLightZone() const;

	UFUNCTION( Category = "SunshineCharacter|SunCharacter|LightTeleport", BlueprintCallable )
	bool EnterLightZone( ALightZone* lightTeleport );

	UFUNCTION( Category = "SunshineCharacter|SunCharacter|LightTeleport", BlueprintCallable )
	bool LeaveLightZone( ALightZone* lightTeleport );

	UFUNCTION( Category = "SunshineCharacter|SunCharacter|LightTeleport", BlueprintCallable )
	bool IsInLightZone() const;

protected:
	/**
	 * \brief Check for LightTeleport as one of the skill and sets index depending on which skill it is
	 */
	UFUNCTION( Category = "SunshineCharacter|SunCharacter|LightTeleport", BlueprintCallable )
	void CheckForLightSkill();

	UPROPERTY( Category = "Skill|SunCharacter|LightTeleport", VisibleAnywhere, BlueprintReadOnly )
	int m_idxLightSkill = -1;

	UPROPERTY( Category = "Skill|SunCharacter|LightTeleport", VisibleAnywhere, BlueprintReadOnly )
	ALightZone* m_lightZone = nullptr;
};
