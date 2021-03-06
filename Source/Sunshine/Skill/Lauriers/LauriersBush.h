// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "LauriersBush.generated.h"

/**
 * Create a bush and hides into it
 */
UCLASS()
class SUNSHINE_API ALauriersBush : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual ~ALauriersBush() = default;

#pragma region Unreal Engine functions
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float deltaTime ) override;
#pragma endregion

	void Init( ASunshineCharacter* character ) override;

protected:
#pragma region Events
	virtual void OnActivationStart_Implementation() override;
	virtual void OnActivationEnd_Implementation() override;
#pragma endregion

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UClass *m_bushClass = nullptr;
};
