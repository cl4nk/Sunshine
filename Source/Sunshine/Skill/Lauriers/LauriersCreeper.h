// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "LauriersCreeper.generated.h"

/**
 * Creates a creeper to be able to go up a wall
 */
UCLASS()
class SUNSHINE_API ALauriersCreeper : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual ~ALauriersCreeper() = default;

#pragma region Unreal Engine functions
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float deltaTime ) override;
#pragma endregion

protected:
#pragma region Events
	virtual void OnActivationStart_Implementation() override;
	virtual void OnActivationEnd_Implementation() override;
#pragma endregion
};
