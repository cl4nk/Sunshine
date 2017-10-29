// Fill out your copyright notice in the Description page of Project Settings.

#include "ArrowLight.h"
#include "SunshineCharacter.h"
#include "SunCharacter.h"
#include "Skill/Bow/LightTeleport.h"

void AArrowLight::OnHitComponent( UPrimitiveComponent* hitComponent, AActor* otherActor,
                                  UPrimitiveComponent* otherComponent,
                                  FVector normalImpulse, const FHitResult& hit )
{
	UE_LOG( LogTemp, Warning, TEXT( "AArrowLight::OnHitComponent() - VALID" ) );
	if ( otherActor->ActorHasTag( "CanTP" ) )
	{
		UE_LOG( LogTemp, Warning, TEXT("AArrowLight::OnHitComponent() - actor has tag, creating light zone for teleportation") );

		ASunCharacter* sunCharacter = Cast<ASunCharacter>( m_sunshineCharacter );
		if ( sunCharacter )
		{
			ALightTeleport* lightTeleport = sunCharacter->GetLightTeleport();
			if ( lightTeleport )
			{
				lightTeleport->CreateNewLightZone( hit.ImpactPoint );
			}
		}
		else
			UE_LOG( LogTemp, Error, TEXT("AArrowLight::OnHitComponent() - owner is not SunCharacter") );
	}
}

void AArrowLight::OnOverlapBegin( UPrimitiveComponent* overlappedComp, AActor* otherActor,
                                  UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep,
                                  const FHitResult& sweepResult )
{
}

void AArrowLight::OnOverlapEnd( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
                                int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult )
{
}
