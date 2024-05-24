// Fill out your copyright notice in the Description page of Project Settings.


#include "Mirror/MirrorEarthManipulatorBPLibrary.h"

TArray<FTransform>
UMirrorEarthManipulatorBPLibrary::GetManipulatorMoveECEFTransform(
    const FTransform& CameraInECEFTransform,
    const FVector& EarthPositionInCameraCoordinate,
    const FVector& AfterMoveEarthPositionInCameraCoordinate,
    const int& Num) {
  TArray<FTransform> Result;

  const FTransform EarthTransformInCameraCoordinate = CameraInECEFTransform.Inverse();

  FVector EarthOriginInCameraCoordinate =
      EarthTransformInCameraCoordinate.GetLocation();

  FVector CameraLocationInCameraCoordinate = FVector(0, 0, 0);

  FVector DirectionInCameraCoordinate =
      EarthPositionInCameraCoordinate - EarthOriginInCameraCoordinate;

  FVector AfterMoveDirectionInCameraCoordinate =
      AfterMoveEarthPositionInCameraCoordinate;

  FQuat EarthPositionMoveToInCameraCoordinateQuat = FQuat::FindBetween(
      DirectionInCameraCoordinate,
      AfterMoveDirectionInCameraCoordinate);

  for (size_t i = 1; i <= Num; i++) {
    const FQuat InterpolateQuat = FMath::QInterpTo(
        FQuat::Identity,
        EarthPositionMoveToInCameraCoordinateQuat,
        i * 1.f / Num,
        1.0);

    FTransform EarthInterpolateTransformInCameraCoordinate =
        EarthTransformInCameraCoordinate;
    EarthInterpolateTransformInCameraCoordinate.SetRotation(
        InterpolateQuat * EarthTransformInCameraCoordinate.GetRotation());

    FTransform AfterMoveCameraInEarthCoordinate =
        FTransform() * EarthInterpolateTransformInCameraCoordinate.Inverse();

    Result.Add(AfterMoveCameraInEarthCoordinate);
  }

  return Result;
}
