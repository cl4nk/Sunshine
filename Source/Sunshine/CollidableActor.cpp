// Fill out your copyright notice in the Description page of Project Settings.

#include "CollidableActor.h"


// Sets default values
ACollidableActor::ACollidableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACollidableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollidableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

