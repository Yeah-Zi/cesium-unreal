// Fill out your copyright notice in the Description page of Project Settings.

#include "Mirror/MirrorManipulatorInputHandler.h"
#include "Mirror/MirrorCoordinatesBPFuncLibrary.h"
#include "Mirror/MirrorEarthManipulatorBPLibrary.h"
void UMirrorManipulatorInputHandler::BeginPlay() {
  Super::BeginPlay();
  APawn* Owner = Cast<APawn>(GetOwner());
  MirrorMoveManagerComponent =
      Owner->GetComponentByClass<UMirrorMoveManagerComponent>();
}

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
    FVector2D MouseScreenPosition) {}

void UMirrorManipulatorInputHandler::LeftMouseButtonReleased(
    FVector2D MouseScreenPosition) {}

void UMirrorManipulatorInputHandler::MouseMoveAxis(float value) {
  FVector2D MouseScreenPosition = GetControllerMousePosition();
  if (value > 0) {
    OnMouseMove(MouseScreenPosition);
  }
}

void UMirrorManipulatorInputHandler::OnMouseMove(
    const FVector2D& MouseScreenPosition) {}

UMirrorDragInputHandler::UMirrorDragInputHandler() {
}

void UMirrorDragInputHandler::BeginPlay() {
  Super::BeginPlay();
  VirtualEarthActor = GetWorld()->SpawnActor<AVirtualEarthActor>();
}

void UMirrorDragInputHandler::BeginDestroy() {
  Super::BeginDestroy();
  GetWorld()->DestroyActor(VirtualEarthActor);
}

void UMirrorDragInputHandler::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  SinceLastDrag += DeltaTime;
}

void UMirrorDragInputHandler::LeftMouseButtonPressed(
    FVector2D MouseScreenPosition) {
  IsLeftMouseButtonPressed = true;
  APawn* Owner = Cast<APawn>(GetOwner());
  APlayerController* Controller =
      Cast<APlayerController>(Owner->GetController());

  FVector UnrealLocation, UnrealDirection;
  Controller->DeprojectMousePositionToWorld(UnrealLocation, UnrealDirection);

  FHitResult HitResultInUnreal =
      UMirrorCoordinatesBPFuncLibrary::LineTraceRealEarthInUnreal(
          UnrealLocation,
          UnrealLocation + 99999999999 * UnrealDirection);

  FVector HitResultLocationInECEF =
      UMirrorCoordinatesBPFuncLibrary::UnrealToECEFLocation(
          HitResultInUnreal.Location);

  FTransform CameraInECEFTransform =
      UMirrorCoordinatesBPFuncLibrary::GetViewECEFTransform(Owner);

  DraggingStartEarthPositionInCameraCoordinate =
      CameraInECEFTransform.InverseTransformPosition(HitResultLocationInECEF);
  DraggingStartVirtualEarthRadius = HitResultLocationInECEF.Length();
}

void UMirrorDragInputHandler::LeftMouseButtonReleased(
    FVector2D MouseScreenPosition) {
  IsLeftMouseButtonPressed = false;
}

void UMirrorDragInputHandler::OnMouseMove(
    const FVector2D& MouseScreenPosition) {
  if (!IsLeftMouseButtonPressed || SinceLastDrag < DraggingInterval ||
      !MirrorMoveManagerComponent || !MirrorMoveManagerComponent->IsValidLowLevelFast()) {
    return;
  }
  SinceLastDrag = 0;

  APawn* Owner = Cast<APawn>(GetOwner());
  APlayerController* Controller =
      Cast<APlayerController>(Owner->GetController());
  FVector UnrealLocation, UnrealDirection;
  Controller->DeprojectMousePositionToWorld(UnrealLocation, UnrealDirection);
  VirtualEarthActor->SetVirtualEarthRadii(
      FVector(DraggingStartVirtualEarthRadius));

  FVector ECEFLocation =
      UMirrorCoordinatesBPFuncLibrary::UnrealToECEFLocation(UnrealLocation);

  FVector ECEFDirection =
      UMirrorCoordinatesBPFuncLibrary::GetUnrealToECEFTransform()
          .TransformVector(UnrealDirection);

  FHitResult HitResultInECEF =
      UMirrorCoordinatesBPFuncLibrary::LineTraceVirtualEarthInECEF(
          VirtualEarthActor,
          ECEFLocation,
          ECEFLocation + 999999999 * ECEFDirection);

  FTransform CameraInECEFTransform =
      UMirrorCoordinatesBPFuncLibrary::GetViewECEFTransform(Owner);

  DraggingNowEarthPositionInCameraCoordinate =
      CameraInECEFTransform.InverseTransformPosition(ECEFLocation);

  TArray<FTransform> MoveTransformInECEF =
      UMirrorEarthManipulatorBPLibrary::GetManipulatorMoveECEFTransform(
          CameraInECEFTransform,
          DraggingStartEarthPositionInCameraCoordinate,
          DraggingNowEarthPositionInCameraCoordinate,
          240);

  MirrorMoveManagerComponent->SetActorTransforms(
      EMirrorCoordinate::ECEF,
      MoveTransformInECEF,
      DraggingInterval);

  /* */
  DraggingStartEarthPositionInCameraCoordinate =
      DraggingNowEarthPositionInCameraCoordinate;
}
