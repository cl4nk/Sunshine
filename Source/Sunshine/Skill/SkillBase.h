// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillBase.generated.h"

class ASunshineCharacter;

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

public:
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

	virtual void Init( ASunshineCharacter* owner );
	void Start();
	void Finish();

protected:
	uint32_t m_manaCost = 0;
	float m_noiseValue = 0.0f;
	bool m_bIsActive = false;
	ASunshineCharacter* m_owner = nullptr;

#pragma region Events
	/**
	 * \brief Called when the skill activation starts, when key is pressed
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OnActivationStart();
	virtual void OnActivationStart_Implementation();

	/**
	 * \brief Called when skill activation ends, when key is released
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OnActivationEnd();
	virtual void OnActivationEnd_Implementation();
#pragma endregion
};
