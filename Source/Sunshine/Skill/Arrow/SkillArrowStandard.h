// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Arrow/SkillArrowBase.h"
#include "SkillArrowStandard.generated.h"

/**
 * Shoots a standard arrow which can kill animals or alert enemies
 */
UCLASS()
class SUNSHINE_API ASkillArrowStandard : public ASkillArrowBase
{
	GENERATED_BODY()

public:
	virtual ~ASkillArrowStandard() = default;

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
