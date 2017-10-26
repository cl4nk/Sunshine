// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "HuntVision.generated.h"

/**
 * Activates hunting vision for a moment
 */
UCLASS()
class SUNSHINE_API AHuntVision : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual ~AHuntVision() = default;

#pragma region Unreal Engine functions
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float deltaTime ) override;
#pragma endregion

	void Init( ASunshineCharacter* owner ) override;
	virtual bool ConsumeMana( int& characterMana ) const override;

protected:
#pragma region Events
	virtual void OnActivationStart_Implementation() override;
	virtual void OnActivationEnd_Implementation() override;
#pragma endregion

	enum SkillState
	{
		Waiting,
		StartHuntVision,
		ActiveHuntVision,
		StopHuntVision
	};
	SkillState m_skillState = Waiting;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float m_maxHuntvisionTime = 30.f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float m_huntVisionTime = 0.f;

private:
	void TickWaiting();
	void TickStartHuntVision();
	void TickActiveHuntVision( const float deltaTime );
	void TickStopHuntVision();
};