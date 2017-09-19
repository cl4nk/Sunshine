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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

protected:
	UFUNCTION( Category = "Notes", BlueprintCallable )
	void AddNote( const float timer, const ENote note );

	UPROPERTY( Category = "Notes", VisibleAnywhere, BlueprintReadOnly )
	TArray<ENote>	m_listNotes;

	UPROPERTY( Category = "Notes", VisibleAnywhere, BlueprintReadOnly )
	TArray<float>	m_listTimers;
};
