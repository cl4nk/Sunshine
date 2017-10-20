// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "Projectile/Arrow/Arrow.h"
#include "Bow.generated.h"

/**
 * Base class for every Bow
 */
UCLASS()
class SUNSHINE_API ABow : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual ~ABow() = default;

#pragma region Unreal Engine functions
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float deltaTime ) override;
#pragma endregion

	void Init( ASunshineCharacter* owner ) override;

protected:
	void Bend();
	void Shoot();
	void Cancel();

	FVector GetAimedLocation() const;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float MaxAimedDistance = 10000.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TSubclassOf<AArrow> m_arrowType;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite )
	AArrow* m_arrowInstance = nullptr;
};
