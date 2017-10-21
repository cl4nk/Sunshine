// Fill out your copyright notice in the Description page of Project Settings.

#include "LightZone.h"

// Sets default values
ALightZone::ALightZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALightZone::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALightZone::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
}
