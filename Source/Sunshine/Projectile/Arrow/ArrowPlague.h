// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/Arrow/ArrowBase.h"
#include "ArrowPlague.generated.h"

/**
 * Plague arrow capable of killing an enemy
 */
UCLASS()
class SUNSHINE_API UArrowPlague : public UArrowBase
{
	GENERATED_BODY()

protected:
	/**
	 * \brief Function called when overlap with another object begins
	 */
	void OnOverlapBegin( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult ) override;

	/**
	 * \brief Function called when overlap with another object ends
	 */
	void OnOverlapEnd( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult ) override;
};
