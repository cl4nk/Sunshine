// Fill out your copyright notice in the Description page of Project Settings.

#include "BowStandard.h"

void ABowStandard::ShootArmed()
{
	Shoot();
}

void ABowStandard::OnActivationStart_Implementation()
{
	Super::OnActivationStart_Implementation();

	if ( m_owner == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "Owner is nullptr !" ) );
		return;
	}

	if ( m_arrowInstance != nullptr )
		return;

	Bend();
}

void ABowStandard::OnActivationEnd_Implementation()
{
	Cancel();

	Super::OnActivationEnd_Implementation();
}