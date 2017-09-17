// Fill out your copyright notice in the Description page of Project Settings.

#include "Arrow.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AArrow::AArrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AArrow::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
}

void AArrow::InitVelocity( FVector direction )
{
	m_rootPrimitiveComponent->AddImpulse( direction * m_powerVelocity );
}

void AArrow::OnOverlapBegin( UPrimitiveComponent* overlappedComp, AActor* otherActor,
								 UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep,
								 const FHitResult& sweepResult )
{
}

void AArrow::OnOverlapEnd( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
							   int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult )
{
}

void AArrow::OnOverlapBeginBase( UPrimitiveComponent* overlappedComp, AActor* otherActor,
									 UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep,
									 const FHitResult& sweepResult )
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ( otherActor != nullptr && otherComp != nullptr && dynamic_cast<AArrow *>( otherActor ) != this )
	{
		OnOverlapBegin( overlappedComp, otherActor, otherComp, otherBodyIndex, bFromSweep, sweepResult );
	}
}

void AArrow::OnOverlapEndBase( UPrimitiveComponent* overlappedComp, AActor* otherActor,
								   UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep,
								   const FHitResult& sweepResult )
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ( otherActor != nullptr && otherComp != nullptr && dynamic_cast<AArrow *>( otherActor ) != this )
	{
		OnOverlapEnd( overlappedComp, otherActor, otherComp, otherBodyIndex, bFromSweep, sweepResult );
	}
}
