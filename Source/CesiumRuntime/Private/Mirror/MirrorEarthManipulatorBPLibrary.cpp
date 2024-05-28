// Fill out your copyright notice in the Description page of Project Settings.

#include "Mirror/MirrorEarthManipulatorBPLibrary.h"

TArray<FTransform>
UMirrorEarthManipulatorBPLibrary::GetManipulatorMoveECEFTransform(
    const FTransform& CameraInECEFTransform,
    const FVector& EarthPositionInCameraCoordinate,
    const FVector& AfterMoveEarthPositionInCameraCoordinate,
    const int& Num) {
  TArray<FTransform> Result;

  const FTransform EarthTransformInCameraCoordinate =
      CameraInECEFTransform.Inverse();

  FVector EarthOriginInCameraCoordinate =
      EarthTransformInCameraCoordinate.GetLocation();

  FVector CameraLocationInCameraCoordinate = FVector(0, 0, 0);

  FVector DirectionInCameraCoordinate =
      (EarthPositionInCameraCoordinate - EarthOriginInCameraCoordinate)
          .GetUnsafeNormal();

  FVector AfterMoveDirectionInCameraCoordinate =
      (AfterMoveEarthPositionInCameraCoordinate - EarthOriginInCameraCoordinate)
          .GetUnsafeNormal();

  FQuat EarthPositionMoveToInCameraCoordinateQuat = FQuat::FindBetween(
      DirectionInCameraCoordinate,
      AfterMoveDirectionInCameraCoordinate);

  for (size_t i = 1; i <= Num; i++) {
    const FQuat InterpolateQuat = FQuat::Slerp(
        FQuat::Identity,
        EarthPositionMoveToInCameraCoordinateQuat,
        FMath::Clamp<double>(i * 1.f / double(Num), 0.f, 1.f));

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
