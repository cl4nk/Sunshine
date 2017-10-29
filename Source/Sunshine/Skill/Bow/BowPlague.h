// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Bow/Bow.h"
#include "BowPlague.generated.h"

/**
 * Shoots an arrow full of plague to kill an enemy
 */
UCLASS()
class SUNSHINE_API ABowPlague : public ABow
{
	GENERATED_BODY()

public:
	virtual ~ABowPlague() = default;

#pragma region Unreal Engine functions
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float deltaTime ) override;
#pragma endregion

	void Init( ASunshineCharacter* owner ) override;

protected:
#pragma region Events
	virtual void OnActivationStart_Implementation() override;
	virtual void OnActivationEnd_Implementation() override;
#pragma endregion

	enum SkillState
	{
		Waiting,
		StartBend,
		BulletTime,
		ShootArrow
	};
	SkillState	m_skillState = Waiting;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	float m_maxBulletTime = 5.f;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	float m_bulletTime = 0.f;

private:
	void TickWaiting();
	void TickStartBend();
	void TickBulletTime( const float deltaTime );
	void TickShootArrow();
};
