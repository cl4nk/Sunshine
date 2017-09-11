// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Arrow/SkillArrowBase.h"
#include "SkillArrowPlague.generated.h"

/**
 * Shoots an arrow full of plague to kill an enemy
 */
UCLASS()
class SUNSHINE_API ASkillArrowPlague : public ASkillArrowBase
{
	GENERATED_BODY()

public:
	virtual ~ASkillArrowPlague() = default;

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
