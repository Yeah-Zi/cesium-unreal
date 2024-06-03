// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mirror/MirrorInputRegisterComponent.h"
#include "MirrorMoveManagerComponent.h"
#include "VirtualEarthActor.h"
#include "MirrorManipulatorInputHandler.generated.h"

/**
 *
 */
UCLASS()
class CESIUMRUNTIME_API UMirrorManipulatorInputHandler
    : public UMirrorInputRegisterComponent {
  GENERATED_BODY()

public:
  UMirrorMoveManagerComponent* MirrorMoveManagerComponent;
  virtual void BeginPlay() override;

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
  UMirrorDragInputHandler();
  virtual void BeginPlay() override;
  virtual void BeginDestroy() override;
  virtual void TickComponent(
      float DeltaTime,
      ELevelTick TickType,
      FActorComponentTickFunction* ThisTickFunction) override;

  bool IsLeftMouseButtonPressed = false;
  bool IsDraggingAny = false;
  double DraggingInterval = 0.1;
  double SinceLastDrag = 0;

  double DraggingStartVirtualEarthRadius;
  FVector DraggingStartEarthPositionInCameraCoordinate;
  FVector DraggingNowEarthPositionInCameraCoordinate;
  FVector2D DraggingStartScreenPosition;
  AVirtualEarthActor* VirtualEarthActor;
  virtual void LeftMouseButtonPressed(FVector2D MouseScreenPosition);
  virtual void LeftMouseButtonReleased(FVector2D MouseScreenPosition);

  virtual void OnMouseMove(const FVector2D& MouseScreenPosition);

};

UCLASS()
class UMirrorScaleInputHandler : public UMirrorManipulatorInputHandler
{
  GENERATED_BODY()
public:
  UMirrorScaleInputHandler();

  virtual void BeginPlay() override;

  virtual void BeginDestroy() override;

  virtual void TickComponent(
      float DeltaTime,
      ELevelTick TickType,
      FActorComponentTickFunction* ThisTickFunction) override;

  virtual void ScrollWheelAxis(float value);

    double ScalingInterval = 0.25;
  double SinceLastScale = 0;
};

UCLASS()
class UMirrorRotateInputHandler : public UMirrorManipulatorInputHandler
{
  GENERATED_BODY()
public:
  UMirrorRotateInputHandler();
  virtual void PressedAction(struct FKey key);
  virtual void ReleasedAction(struct FKey key);

  virtual void MouseMidButtonPressed();

  virtual void MouseMidButtonReleased();

  virtual void OnMouseMove(const FVector2D& MouseScreenPosition);

  FVector firstFocusPointInECEFCoordinate;
  FVector2D currentCursorScreenPosition;
  FVector2D lastCursorScreenPosition;
  FVector2D firstCursorScreenPosition;

  bool bRotateClickDown = false;
  bool bClickOnEarth = false;
};

UCLASS()
class UMirrorThrowInputHandler : public UMirrorManipulatorInputHandler
{
  GENERATED_BODY()
public:
  UMirrorThrowInputHandler();

  virtual void BeginPlay() override;

  virtual void TickComponent(
      float DeltaTime,
      ELevelTick TickType,
      FActorComponentTickFunction* ThisTickFunction) override;

  virtual void LeftMouseButtonPressed(FVector2D MouseScreenPosition);

  virtual void LeftMouseButtonReleased(FVector2D MouseScreenPosition);

  bool IsLeftMouseButtonPressed = false;

  bool IsFirstCursorClickOnEarth = false;

  double ThrowStartVirtualEarthRadius;

  FVector ThrowStartEarthPositionInCameraCoordinate;

  AVirtualEarthActor* VirtualEarthActor;

  double ThrowInterval = 0.25;

  double AfterThrowClickStartTime = 0;

  double ThrowTime = 0;
};
