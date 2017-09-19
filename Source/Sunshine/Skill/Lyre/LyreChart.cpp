// Fill out your copyright notice in the Description page of Project Settings.

#include "LyreChart.h"

// Sets default values for this component's properties
ULyreChart::ULyreChart()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

int ULyreChart::GetNoteCount() const
{
	const int32 noteCount = m_listNotes.Num();

	if ( noteCount != m_listTimers.Num() )
	{
		UE_LOG( LogTemp, Error, TEXT( "Note and Timer haven't got the same amout of values !" ) );
		return -1;
	}

	return noteCount;
}

ENote ULyreChart::GetNoteAt( const int noteIndex ) const
{
	if ( noteIndex < 0 || noteIndex >= m_listNotes.Num() )
	{
		UE_LOG( LogTemp, Error, TEXT( "GetNoteAt(%d) - bad noteIndex" ), noteIndex );
		return ENote::N_NONE;
	}

	return m_listNotes[noteIndex];
}

float ULyreChart::GetTimerBeforeNoteAt( const int noteIndex ) const
{
	if ( noteIndex < 0 || noteIndex >= m_listTimers.Num() )
	{
		UE_LOG( LogTemp, Error, TEXT( "GetTimerBeforeNoteAt(%d) - bad noteIndex" ), noteIndex );
		return -1.f;
	}
	
	return m_listTimers[noteIndex];
}

void ULyreChart::AddNote( const float timer, const ENote note )
{
	UE_LOG( LogTemp, Warning, TEXT( "AddNote(%f, %d)" ), timer, (int8)note );

	m_listTimers.Add( timer );
	m_listNotes.Add( note );
}
