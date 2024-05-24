// Fill out your copyright notice in the Description page of Project Settings.


#include "Mirror/MirrorEarthManipulator.h"

// Sets default values
AMirrorEarthManipulator::AMirrorEarthManipulator()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMirrorEarthManipulator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMirrorEarthManipulator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMirrorEarthManipulator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

