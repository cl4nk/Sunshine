// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Bow/Bow.h"
#include "BowStandard.generated.h"

/**
 * 
 */
UCLASS()
class SUNSHINE_API ABowStandard : public ABow
{
	GENERATED_BODY()

public:
	void ShootArmed();
	
protected:
#pragma region Events
	virtual void OnActivationStart_Implementation() override;
	virtual void OnActivationEnd_Implementation() override;
#pragma endregion
};
