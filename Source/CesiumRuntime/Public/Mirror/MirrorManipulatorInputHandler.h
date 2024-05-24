// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mirror/MirrorInputRegisterComponent.h"
#include "MirrorManipulatorInputHandler.generated.h"

/**
 *
 */
UCLASS()
class CESIUMRUNTIME_API UMirrorManipulatorInputHandler
    : public UMirrorInputRegisterComponent {
  GENERATED_BODY()

public:
  FVector2D GetControllerMousePosition();

  virtual void PressedAction(struct FKey key);
  virtual void ReleasedAction(struct FKey key);

  virtual void LeftMouseButtonPressed(FVector2D MouseScreenPosition);
  virtual void LeftMouseButtonReleased(FVector2D MouseScreenPosition);

  virtual void MouseMoveAxis(float value);

  virtual void OnMouseMove(const FVector2D& MouseScreenPosition);
};

UCLASS()
class CESIUMRUNTIME_API UMirrorDragInputHandler
    : public UMirrorManipulatorInputHandler {
  GENERATED_BODY()
public:
  bool IsLeftMouseButtonPressed = false;

  double DraggingInterval = 0.2;

  double DraggingStartVirtualEarthRadius;
  FVector DraggingStartEarthPositionInCameraCoordinate;
  FVector DraggingNowEarthPositionInCameraCoordinate;

  virtual void LeftMouseButtonPressed(FVector2D MouseScreenPosition);
  virtual void LeftMouseButtonReleased(FVector2D MouseScreenPosition);

  virtual void OnMouseMove(const FVector2D& MouseScreenPosition);

};
