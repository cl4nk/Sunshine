// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"

class ASunCharacter;
class ALightZone;

#include "LightTeleport.generated.h"

/**
 * Teleports from a light arrow to the other light arrow
 */
UCLASS()
class SUNSHINE_API ALightTeleport : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual ~ALightTeleport() = default;

#pragma region Unreal Engine functions
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float deltaTime ) override;
#pragma endregion

	virtual void Init( ASunshineCharacter* owner ) override;
	
	void CreateNewLightZone( const FVector& worldLocation );

protected:
#pragma region Events
	virtual void OnActivationStart_Implementation() override;
	virtual void OnActivationEnd_Implementation() override;
#pragma endregion

	bool CanTeleport() const;
	void TeleportCharacter() const;
	void Teleport( ASunCharacter* sunCharacter, ALightZone* start, ALightZone* destination ) const;

	enum SkillState
	{
		Waiting,
		Cooldown
	};
	SkillState	m_skillState = Waiting;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	ALightZone* m_lightZoneOne = nullptr;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	ALightZone* m_lightZoneTwo = nullptr;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	bool m_bIsFirstZone = true;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float m_cooldownBetweenUse = 3.f;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	float m_cooldownSinceLastUse = 0.f;

	UPROPERTY( Category = "Light", EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<ALightZone> m_lightZoneClass;

private:
	void TickWaiting();
	void TickCooldown( const float deltaTime );
};
