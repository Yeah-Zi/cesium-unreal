// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MirrorManipulatorInputHandler.h"
#include "MirrorMoveManagerComponent.h"
#include "../CesiumGlobeAnchorComponent.h"
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
  UCesiumGlobeAnchorComponent* CesiumGlobeAnchorComponent = nullptr;

  UPROPERTY(VisibleAnywhere)
  UMirrorMoveManagerComponent* MoveManager = nullptr;

  UPROPERTY(VisibleAnywhere)
  UMirrorDragInputHandler* DragInputHandler = nullptr;

  UPROPERTY(VisibleAnywhere)
  UCameraComponent* Camera = nullptr;

  UPROPERTY(VisibleAnywhere)
  UMirrorScaleInputHandler* ScaleInputHandler = nullptr;

  UPROPERTY(VisibleAnywhere)
  UMirrorRotateInputHandler* RotateInputHandler = nullptr;

  UPROPERTY(VisibleAnywhere)
  UMirrorThrowInputHandler* ThrowInputHandler = nullptr;
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      class UInputComponent* PlayerInputComponent) override;
};
