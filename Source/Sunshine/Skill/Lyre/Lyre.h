// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "LyreChart.h"
#include "Lyre.generated.h"

/**
 * Play some Lyre to execute an effect
 */
UCLASS()
class SUNSHINE_API ALyre : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual ~ALyre() = default;

#pragma region Unreal Engine functions
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float deltaTime ) override;
#pragma endregion

	virtual void Init( ASunshineCharacter* owner ) override;
	virtual bool ConsumeMana( int& characterMana ) const override;

	UFUNCTION( Category = "Chart", BlueprintCallable )
	void SelectPrevChart();

	UFUNCTION( Category = "Chart", BlueprintCallable )
	void SelectNextChart();

protected:
#pragma region Events
	void OnActivationStart_Implementation() override;
	void OnActivationEnd_Implementation() override;

	/**
	 * \brief Called when player fails its QTE
	 */
	UFUNCTION( Category = "Events", BlueprintNativeEvent )
	void OnFailedPlaying();
	void OnFailedPlaying_Implementation();
#pragma endregion

	enum SkillState
	{
		Waiting,
		StartPlaying,
		Playing,
		FailedEffect,
		ExecuteEffect,
		StopPlaying,
	};
	SkillState m_skillState = Waiting;

#pragma region Charts	
	/**
	 * \brief Max interval between the input and the note to valid the note
	 * \note This value is before and after the note. Meaning the total time to hit the note is *2
	 */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	float m_maxIntervalForOneNote = 0.5f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TArray<TSubclassOf<ULyreChart>>	m_chartsList;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	ULyreChart* m_activeChart = nullptr;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	int m_currentChartIdx = 0;
#pragma endregion

#pragma region Note
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	float m_timeSinceLastNote = 0.f;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	float m_nextTimerBeforeNote = 0.f;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	ENote m_nextNote = ENote::N_NONE;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	int m_currentNoteIdx = 0;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	int m_totalNotesCount = 0;
#pragma endregion

private:
	void GetNextNote();

	template<ENote TNote>
	void ClickOnNote();

	void TickWaiting();
	void TickStartPlaying();
	void TickPlaying( float deltaTime );
	void TickFailedEffect();
	void TickExecuteEffect();
	void TickStopPlaying();
};
