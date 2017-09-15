// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Bow/BowBase.h"
#include "BowPlague.generated.h"

/**
 * Shoots an arrow full of plague to kill an enemy
 */
UCLASS()
class SUNSHINE_API ABowPlague : public ABowBase
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

protected:
#pragma region Events
	virtual void OnActivationStart_Implementation() override;
	virtual void OnActivationEnd_Implementation() override;
#pragma endregion
};
