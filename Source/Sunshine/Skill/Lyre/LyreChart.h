// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LyreChart.generated.h"

UENUM(BlueprintType)
enum class ENote : uint8
{
	N_Do	UMETA( DisplayName = "Do" ),
	N_Re	UMETA( DisplayName = "Re" ),
	N_Mi	UMETA( DisplayName = "Mi" ),
	N_Fa	UMETA( DisplayName = "Fa" ),
	N_Sol	UMETA( DisplayName = "Sol" ),
	N_La	UMETA( DisplayName = "La" ),
	N_Si	UMETA( DisplayName = "Si" ),

	N_NONE	UMETA( Hidden )
};

USTRUCT(BlueprintType)
struct FApproachNote
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float m_timer;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	ENote m_note;
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUNSHINE_API ULyreChart : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULyreChart();

	UFUNCTION()
	int	GetNoteCount() const;

	UFUNCTION()
	ENote GetNoteAt( const int noteIndex ) const;

	UFUNCTION()
	float GetTimerBeforeNoteAt( const int noteIndex ) const;

	// TODO: not possible for GD because UActorComponent does not support BlueprintImplementableEvent
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	//void InitChart();

protected:
	UFUNCTION( Category = "Notes", BlueprintCallable )
	void AddNote( const float timer, const ENote note );

	UPROPERTY( Category = "Notes", EditDefaultsOnly, BlueprintReadOnly )
	TArray<FApproachNote> m_listNotes;
};
