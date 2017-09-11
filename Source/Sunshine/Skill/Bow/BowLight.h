// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Bow/BowBase.h"
#include "BowLight.generated.h"

/**
 * Shoots an arrow of light that notifies enemies permits teleport
 */
UCLASS()
class SUNSHINE_API ABowLight : public ABowBase
{
	GENERATED_BODY()

public:
	virtual ~ABowLight() = default;

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
