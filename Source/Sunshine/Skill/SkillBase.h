// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillBase.generated.h"

UCLASS()
class SUNSHINE_API ASkillBase : public AActor
{
	GENERATED_BODY()

public:
	// Does not Tick when created
	ASkillBase();
	virtual ~ASkillBase() = default;

#pragma region Unreal Engine functions
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick( float deltaTime ) override;
#pragma endregion

#pragma region Events
	/**
	 * \brief Called when the skill starts
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OnActivationStart();
	virtual void OnActivationStart_Implementation();

	/**
	 * \brief Called when skill ends
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OnActivationEnd();
	virtual void OnActivationEnd_Implementation();
#pragma endregion

#pragma region Getters
	/**
	 * \brief Get the Mana cost of the Skill
	 */
	uint32_t GetManaCost() const;

	/**
	 * \brief Get the Noise value made by the skill usage
	 */
	float GetNoiseValue() const;
#pragma endregion

protected:
	uint32_t m_manaCost = 0;
	float m_noiseValue = 0.0f;
};
