// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "SkillArrowBase.generated.h"

/**
 * Base class for every Arrow
 */
UCLASS()
class SUNSHINE_API ASkillArrowBase : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual ~ASkillArrowBase() = default;

#pragma region Unreal Engine functions
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float deltaTime ) override;
#pragma endregion

#pragma region Events
	virtual void OnActivationStart_Implementation() override;
	virtual void OnActivationEnd_Implementation() override;
#pragma endregion
};
