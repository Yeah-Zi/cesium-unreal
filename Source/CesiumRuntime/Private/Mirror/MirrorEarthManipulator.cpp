// Fill out your copyright notice in the Description page of Project Settings.

#include "Mirror/MirrorEarthManipulator.h"

// Sets default values
AMirrorEarthManipulator::AMirrorEarthManipulator() {
  // Set this pawn to call Tick() every frame.  You can turn this off to improve
  // performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  MoveManager =
      CreateDefaultSubobject<UMirrorMoveManagerComponent>(TEXT("MoveManager"));

  DragInputHandler =
      CreateDefaultSubobject<UMirrorDragInputHandler>(TEXT("DragInputHandler"));
  Camera =
      CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  SetRootComponent(Camera);
}

// Called when the game starts or when spawned
void AMirrorEarthManipulator::BeginPlay() {
  Super::BeginPlay();
  GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

// Called every frame
void AMirrorEarthManipulator::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Called to bind functionality to input
void AMirrorEarthManipulator::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
}
