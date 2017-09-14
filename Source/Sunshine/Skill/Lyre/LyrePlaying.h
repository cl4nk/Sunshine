// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "LyrePlaying.generated.h"

/**
 * Play some Lyre to execute an effect
 */
UCLASS()
class SUNSHINE_API ALyrePlaying : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual ~ALyrePlaying() = default;

#pragma region Unreal Engine functions
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float deltaTime ) override;
#pragma endregion

#pragma region Events
	void OnActivationStart_Implementation() override;
	void OnActivationEnd_Implementation() override;

	/**
	 * \brief Called when player fails its QTE
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OnFailedPlaying();
	void OnFailedPlaying_Implementation();
#pragma endregion
};
