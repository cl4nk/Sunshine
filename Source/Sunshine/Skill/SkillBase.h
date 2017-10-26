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
	int GetManaCost() const;

	/**
	 * \brief Get the Noise value made by the skill usage
	 */
	float GetNoiseValue() const;
#pragma endregion

	virtual void Init( ASunshineCharacter* owner );
	void Start();
	void Finish();

	/**
	 * \brief Consumes mana from the parameter
	 * \param characterMana _IN_ A reference on the character's mana
	 * \return True if consumed some mana, false otherwise
	 */
	virtual bool ConsumeMana( int& characterMana ) const;

protected:
	/**
	 * \brief Mana cost of the skill ON CALL
	 */
	UPROPERTY( Category = "Skill|Stats", EditDefaultsOnly, BlueprintReadOnly )
	int		m_manaCost = 0;

	/**
	 * \brief Noise value of the skill ON CALL
	 */
	UPROPERTY( Category = "Skill|Stats", EditDefaultsOnly, BlueprintReadOnly )
	float	m_noiseValue = 0.0f;

	bool	m_bIsActive = false;
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
