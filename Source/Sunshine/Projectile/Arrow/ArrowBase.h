// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ArrowBase.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUNSHINE_API UArrowBase : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArrowBase();

#pragma region Unreal Engine functions
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent( float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction ) override;
#pragma endregion

protected:
	/**
	 * \brief Function called when overlap with another object begins
	 */
	virtual void OnOverlapBegin( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult );

	/**
	 * \brief Function called when overlap with another object ends
	 */
	virtual void OnOverlapEnd( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult );

private:
	/**
	 * \brief Function called when overlap with another object begins
	 * \note This private function will call OnOverlapBegin(), which is virtual and can be overriden
	 */
	void OnOverlapBeginBase( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult );

	/**
	 * \brief Function called when overlap with another object ends
	 * \note This private function will call OnOverlapEnd(), which is virtual and can be overriden
	 */
	void OnOverlapEndBase( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult );
};
