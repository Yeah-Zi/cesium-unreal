// Fill out your copyright notice in the Description page of Project Settings.

#include "Mirror/MirrorEarthManipulator.h"
#include "Mirror/MirrorCoordinatesBPFuncLibrary.h"
// Sets default values
AMirrorEarthManipulator::AMirrorEarthManipulator() {
  // Set this pawn to call Tick() every frame.  You can turn this off to improve
  // performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  MoveManager =
      CreateDefaultSubobject<UMirrorMoveManagerComponent>(TEXT("MoveManager"));

  DragInputHandler =
      CreateDefaultSubobject<UMirrorDragInputHandler>(TEXT("DragInputHandler"));

  ScaleInputHandler = 
    CreateDefaultSubobject<UMirrorScaleInputHandler>(TEXT("ScaleInputHandler"));

  RotateInputHandler = CreateDefaultSubobject<UMirrorRotateInputHandler>(
      TEXT("RotateInputHandler"));

  RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
  SetRootComponent(RootComponent);

  Camera =
      CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  Camera->AttachToComponent(
      RootComponent,
      FAttachmentTransformRules::KeepRelativeTransform);
  bUseControllerRotationPitch = false;
  bUseControllerRotationYaw = false;
  bUseControllerRotationRoll = false;
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
