// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

UCLASS()
class SUNSHINE_API AArrow : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AArrow();

#pragma region Unreal Engine functions
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick( float deltaTime ) override;
#pragma endregion

	void InitVelocity( FVector direction );

protected:
	/**
	 * \brief Function called when overlap with another object begins
	 */
	UFUNCTION( Category = "Collision", BlueprintCallable )
	virtual void OnOverlapBegin( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
	                             int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult );

	/**
	 * \brief Function called when overlap with another object ends
	 */
	UFUNCTION( Category = "Collision", BlueprintCallable )
	virtual void OnOverlapEnd( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
	                           int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult );

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float m_powerVelocity = 2000.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UPrimitiveComponent* m_rootPrimitiveComponent = nullptr;

private:
	/**
	 * \brief Function called when overlap with another object begins
	 * \note This private function will call OnOverlapBegin(), which is virtual and can be overriden
	 */
	UFUNCTION( Category = "Collision", BlueprintCallable )
	void OnOverlapBeginBase( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
	                         int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult );

	/**
	 * \brief Function called when overlap with another object ends
	 * \note This private function will call OnOverlapEnd(), which is virtual and can be overriden
	 */
	UFUNCTION( Category = "Collision", BlueprintCallable )
	void OnOverlapEndBase( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
	                       int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult );
};
