// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MirrorManipulatorInputHandler.h"
#include "MirrorMoveManagerComponent.h"
#include "MirrorEarthManipulator.generated.h"

UCLASS()
class CESIUMRUNTIME_API AMirrorEarthManipulator : public APawn {
  GENERATED_BODY()

public:
  // Sets default values for this pawn's properties
  AMirrorEarthManipulator();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  UPROPERTY(VisibleAnywhere)
  UMirrorMoveManagerComponent* MoveManager;

  UPROPERTY(VisibleAnywhere)
  UMirrorDragInputHandler* DragInputHandler;

  UPROPERTY(VisibleAnywhere)
  UCameraComponent* Camera;

  UPROPERTY(VisibleAnywhere)
  UMirrorScaleInputHandler* ScaleInputHandler;
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      class UInputComponent* PlayerInputComponent) override;
};
