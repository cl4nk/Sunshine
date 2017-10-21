// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SunshineCharacter.h"
#include "ShineCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SUNSHINE_API AShineCharacter : public ASunshineCharacter
{
	GENERATED_BODY()

public:
	virtual ~AShineCharacter() = default;

	virtual void ChangeMultiSkill( float rate ) override;
};
