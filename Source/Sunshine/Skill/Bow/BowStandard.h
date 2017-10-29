// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Bow/Bow.h"
#include "Skill/Weapon.h"
#include "BowStandard.generated.h"

/**
 * 
 */
UCLASS()
class SUNSHINE_API ABowStandard : public ABow, public IWeapon
{
	GENERATED_BODY()

public:
	virtual ~ABowStandard() = default;

#pragma region Unreal Engine functions
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float deltaTime ) override;
#pragma endregion

	void Init( ASunshineCharacter* owner ) override;

	void ShootIfArmed() override;
	
protected:
#pragma region Events
	virtual void OnActivationStart_Implementation() override;
	virtual void OnActivationEnd_Implementation() override;
#pragma endregion

	enum SkillState
	{
		Waiting,
		StartBend,
		IsArmed,
		ShootArrow,
		CancelShoot,
		PostAction
	};
	SkillState	m_skillState = Waiting;

private:
	void TickWaiting();
	void TickStartBend();
	void TickIsArmed();
	void TickShootArrow();
	void TickCancelShoot();
	void TickPostAction();
};
