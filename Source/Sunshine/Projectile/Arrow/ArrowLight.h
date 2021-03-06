// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/Arrow/Arrow.h"
#include "Skill/Bow/LightZone.h"
#include "ArrowLight.generated.h"

/**
 * Light arrow capable of creating light zones that Sun can use to teleport
 */
UCLASS()
class SUNSHINE_API AArrowLight : public AArrow
{
	GENERATED_BODY()

protected:
	/**
	 * \brief Function called when hiting another actor
	 */
	void OnHitComponent( UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
	                     FVector normalImpulse, const FHitResult& hit ) override;

	/**
	 * \brief Function called when overlap with another object begins
	 */
	void OnOverlapBegin( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult ) override;

	/**
	 * \brief Function called when overlap with another object ends
	 */
	void OnOverlapEnd( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult ) override;
};
