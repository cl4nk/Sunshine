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

protected:
#pragma region Events
	virtual void OnActivationStart_Implementation() override;
	virtual void OnActivationEnd_Implementation() override;
#pragma endregion
};
