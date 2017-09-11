// Fill out your copyright notice in the Description page of Project Settings.

#include "ArrowBase.h"

UArrowBase::UArrowBase()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UArrowBase::BeginPlay()
{
	Super::BeginPlay();

	//collisionBox->OnComponentBeginOverlap.AddDynamic(this, &UArrowBase::OnOverlapBegin);
}

void UArrowBase::TickComponent( float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction )
{
	Super::TickComponent( deltaTime, tickType, thisTickFunction );
}

void UArrowBase::OnOverlapBegin( UPrimitiveComponent* overlappedComp, AActor* otherActor,
                                 UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep,
                                 const FHitResult& sweepResult )
{
}

void UArrowBase::OnOverlapEnd( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
                               int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult )
{
}

void UArrowBase::OnOverlapBeginBase( UPrimitiveComponent* overlappedComp, AActor* otherActor,
                                     UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep,
                                     const FHitResult& sweepResult )
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ( otherActor != nullptr && dynamic_cast<UArrowBase *>( otherActor ) != this && otherComp != nullptr )
	{
		OnOverlapBegin( overlappedComp, otherActor, otherComp, otherBodyIndex, bFromSweep, sweepResult );
	}
}

void UArrowBase::OnOverlapEndBase( UPrimitiveComponent* overlappedComp, AActor* otherActor,
                                   UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep,
                                   const FHitResult& sweepResult )
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ( otherActor != nullptr && dynamic_cast<UArrowBase *>( otherActor ) != this && otherComp != nullptr )
	{
		OnOverlapEnd( overlappedComp, otherActor, otherComp, otherBodyIndex, bFromSweep, sweepResult );
	}
}
