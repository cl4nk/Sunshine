// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "LauriersTree.generated.h"

/**
 * Transforms into a tree to avoid being detected
 */
UCLASS()
class SUNSHINE_API ALauriersTree : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual ~ALauriersTree() = default;

#pragma region Unreal Engine functions
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float deltaTime ) override;
#pragma endregion

	void Init( ASunshineCharacter* owner ) override;
	virtual bool ConsumeMana( int& characterMana ) const override;

protected:
#pragma region Events
	virtual void OnActivationStart_Implementation() override;
	virtual void OnActivationEnd_Implementation() override;
#pragma endregion

	UFUNCTION( BlueprintCallable )
	void CancelTransform();

	enum SkillState
	{
		Waiting,
		StartTransformation,
		IsTransformed,
		StopTransformation
	};
	SkillState	m_skillState = Waiting;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	float m_maxTransformationTime = 5.f;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	float m_transformationTime = 0.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UClass *m_treeClass = nullptr;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	AActor *m_treeInstance = nullptr;

private:
	void TickWaiting();
	void TickStartTransformation();
	void TickIsTransformed( const float deltaTime );
	void TickStopTransformation();
};
