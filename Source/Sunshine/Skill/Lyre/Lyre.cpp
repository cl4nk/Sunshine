// Fill out your copyright notice in the Description page of Project Settings.

#include "Lyre.h"
#include "SunshineCharacter.h"

#pragma region Unreal Engine functions
void ALyre::BeginPlay()
{
	Super::BeginPlay();
}

void ALyre::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	switch ( m_skillState )
	{
		case Waiting:
			TickWaiting();
			break;
		case StartPlaying:
			TickStartPlaying();
			break;
		case Playing:
			TickPlaying( deltaTime );
			break;
		case FailedEffect:
			TickFailedEffect();
			break;
		case ExecuteEffect:
			TickExecuteEffect();
			break;
		case StopPlaying:
			TickStopPlaying();
			break;
	}
}
#pragma endregion

void ALyre::Init( ASunshineCharacter* owner )
{
	Super::Init( owner );

	// Mana cost and noise depends on the song played
	m_manaCost = 0;
	m_noiseValue = 0.0f;

	m_skillState = Waiting;

	const int32 num = m_chartsList.Num();
	if ( num == 0 )
	UE_LOG( LogTemp, Error, TEXT( "Charts list is empty !" ) );

	// Create new InputCmoponent to manage this class inputs
	InputComponent = NewObject<UInputComponent>();

	// if created
	if ( InputComponent )
	{
		// register the InputComponent to the world
		//InputComponent->RegisterComponent();
		// tell this InputComponent if he has an input on some keys, every "underpriorised" InputComponent won't trigger its inputs
		InputComponent->bBlockInput = bBlockInput;

		// Register
		InputComponent->BindAction( "SkillOne", IE_Pressed, this, &ALyre::ClickOnNote<ENote::N_Do> );
		InputComponent->BindAction( "SkillTwo", IE_Pressed, this, &ALyre::ClickOnNote<ENote::N_Re> );
		InputComponent->BindAction( "SkillUltimate", IE_Pressed, this, &ALyre::ClickOnNote<ENote::N_Mi> );
	}
	else
	UE_LOG( LogTemp, Error, TEXT( "InputComponent is nullptr !" ) );
}

bool ALyre::ConsumeMana( int& characterMana ) const
{
	if ( !m_activeChart )
		return false;

	const int chartManaCost = m_activeChart->GetManaCost();
	if ( characterMana < chartManaCost )
		return false;

	characterMana -= chartManaCost;
	return true;
}

void ALyre::SelectPrevChart()
{
	--m_currentChartIdx;

	if ( m_currentChartIdx < 0 )
		m_currentChartIdx = m_chartsList.Num() - 1;
}

void ALyre::SelectNextChart()
{
	++m_currentChartIdx;

	if ( m_currentChartIdx >= m_chartsList.Num() )
		m_currentChartIdx = 0;
}

#pragma region Events
void ALyre::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	if ( m_owner == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "Owner is nullptr !" ) );
		return;
	}

	if ( m_chartsList.Num() == 0 )
	{
		UE_LOG( LogTemp, Error, TEXT( "Charts list is empty !" ) );
		return;
	}

	m_skillState = StartPlaying;
	SetActorTickEnabled( true );
}

void ALyre::OnActivationEnd_Implementation()
{
	// Do nothing

	Super::OnActivationEnd_Implementation();
}

void ALyre::OnFailedPlaying_Implementation()
{
	m_skillState = FailedEffect;
}
#pragma endregion

void ALyre::GetNextNote()
{
	if ( m_activeChart == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "GetNextNote() - m_activeChart == nullptr" ) );
		return;
	}

	m_nextNote = m_activeChart->GetNoteAt( m_currentNoteIdx );
	m_nextTimerBeforeNote = m_activeChart->GetTimerBeforeNoteAt( m_currentNoteIdx );
}

template<ENote TNote>
void ALyre::ClickOnNote()
{
	UE_LOG( LogTemp, Warning, TEXT( "ClickOnNote() [%d]" ), (int8)TNote );

	if ( TNote != m_nextNote
		|| m_timeSinceLastNote < m_nextTimerBeforeNote - m_maxIntervalForOneNote
		|| m_timeSinceLastNote > m_nextTimerBeforeNote + m_maxIntervalForOneNote )
	{
		OnFailedPlaying();
		return;
	}

	++m_currentNoteIdx;

	if ( m_currentNoteIdx >= m_totalNotesCount )
	{
		m_skillState = ExecuteEffect;
		return;
	}

	m_timeSinceLastNote -= m_nextTimerBeforeNote;

	GetNextNote();
}

void ALyre::TickWaiting()
{
	SetActorTickEnabled( false );
}

void ALyre::TickStartPlaying()
{
	UE_LOG( LogTemp, Warning, TEXT( "TickStartPlaying()" ) );

	m_currentNoteIdx = 0;
	m_timeSinceLastNote = 0;

	m_activeChart = m_chartsList[m_currentChartIdx].GetDefaultObject();
	if ( m_activeChart == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "TickStartPlaying() -- Spawned failed" ) );
		return;
	}

	m_totalNotesCount = m_activeChart->GetNoteCount();

	EnableInput( Cast<APlayerController>( m_owner->GetController() ) );

	GetNextNote();

	m_skillState = Playing;
}

void ALyre::TickPlaying( float deltaTime )
{
	m_timeSinceLastNote += deltaTime;

	UE_LOG( LogTemp, Warning, TEXT( "TickPlaying() - AVANT CLIC [%f]" ),
		m_nextTimerBeforeNote - m_timeSinceLastNote );

	if ( m_timeSinceLastNote > m_nextTimerBeforeNote + m_maxIntervalForOneNote )
		OnFailedPlaying();
}

void ALyre::TickFailedEffect()
{
	UE_LOG( LogTemp, Warning, TEXT( "TickFailedEffect()" ) );

	m_skillState = StopPlaying;
}

void ALyre::TickExecuteEffect()
{
	UE_LOG( LogTemp, Warning, TEXT( "TickExecuteEffect()" ) );

	m_skillState = StopPlaying;
}

void ALyre::TickStopPlaying()
{
	UE_LOG( LogTemp, Warning, TEXT( "TickStopPlaying()" ) );

	m_activeChart->DestroyComponent();
	m_activeChart = nullptr;
	DisableInput( Cast<APlayerController>( m_owner->GetController() ) );
	m_skillState = Waiting;
}
