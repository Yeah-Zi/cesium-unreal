// Fill out your copyright notice in the Description page of Project Settings.


#include "Mirror/MirrorManipulatorInputHandler.h"
#include "Mirror/MirrorCoordinatesBPFuncLibrary.h"
FVector2D UMirrorManipulatorInputHandler::GetControllerMousePosition() {
  APawn* Owner = Cast<APawn>(GetOwner());
  APlayerController* Controller =
      Cast<APlayerController>(Owner->GetController());

  FVector2D MouseScreenPosition;
  Controller->GetMousePosition(MouseScreenPosition.X, MouseScreenPosition.Y);
  return MouseScreenPosition;
}

void UMirrorManipulatorInputHandler::PressedAction(FKey key) {
  FVector2D MouseScreenPosition = GetControllerMousePosition();
  if (key == EKeys::LeftMouseButton) {
    LeftMouseButtonPressed(MouseScreenPosition);
  }
}

void UMirrorManipulatorInputHandler::ReleasedAction(FKey key) {
  FVector2D MouseScreenPosition = GetControllerMousePosition();
  if (key == EKeys::LeftMouseButton) {
    LeftMouseButtonReleased(MouseScreenPosition);
  }
}

void UMirrorManipulatorInputHandler::LeftMouseButtonPressed(
    FVector2D MouseScreenPosition) {

}

void UMirrorManipulatorInputHandler::LeftMouseButtonReleased(
    FVector2D MouseScreenPosition) {

}

void UMirrorManipulatorInputHandler::MouseMoveAxis(float value) {
  FVector2D MouseScreenPosition = GetControllerMousePosition();
  if (value > 0) {
    OnMouseMove(MouseScreenPosition);
  }
}

void UMirrorManipulatorInputHandler::OnMouseMove(
    const FVector2D& MouseScreenPosition) {}



void UMirrorDragInputHandler::LeftMouseButtonPressed(
    FVector2D MouseScreenPosition) {
  IsLeftMouseButtonPressed = true;
  DraggingStartEarthPositionInCameraCoordinate;

  APawn* Owner = Cast<APawn>(GetOwner());
  APlayerController* Controller =
      Cast<APlayerController>(Owner->GetController());

  FVector UnrealLocation, UnrealDirection;
  Controller->DeprojectMousePositionToWorld(UnrealLocation, UnrealDirection);


  FHitResult HitResultInUnreal =
      UMirrorCoordinatesBPFuncLibrary::LineTraceRealEarthInUnreal(
          UnrealLocation,
          UnrealLocation + 99999999999 * UnrealDirection);

  FTransform CameraInUnrealTransform;
  FVector Location;
  FRotator Rotation;
  Controller->GetPlayerViewPoint(Location, Rotation);
  CameraInUnrealTransform.SetLocation(Location);
  CameraInUnrealTransform.SetRotation(FQuat(Rotation));

  //if (UMirrorCoordinatesBPFuncLibrary::LineTraceRealEarthInECEF()) {
  //}
}

void UMirrorDragInputHandler::LeftMouseButtonReleased(
    FVector2D MouseScreenPosition) {
  IsLeftMouseButtonPressed =  false;
}

void UMirrorDragInputHandler::OnMouseMove(
    const FVector2D& MouseScreenPosition) {}
