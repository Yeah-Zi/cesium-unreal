// Fill out your copyright notice in the Description page of Project Settings.

#include "Mirror/MirrorEarthManipulatorBPLibrary.h"
#include "Mirror/MirrorCoordinatesBPFuncLibrary.h"
#include "Mirror/VirtualEarthActor.h"
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

TArray<FTransform>
UMirrorEarthManipulatorBPLibrary::GetManipulatorScaleECEFTransform(
    const FTransform& CameraInECEFTransform,
    const FVector& FocusPositionInCameraCoordinate,
    const FVector& CursorPositionInCameraCoordinate,
    const FVector& CursorDirectionInCameraCoordinate,
    const double& Scale,
    const int& Num) {
  FTransform EarthTransformInCameraCoordinate = CameraInECEFTransform.Inverse();

  FVector BeforeScaleFocusPositionToEarthCenterDirectionInCameraCoordiante =
      (FocusPositionInCameraCoordinate -
       EarthTransformInCameraCoordinate.GetLocation())
          .GetUnsafeNormal();

  double FocusPositionRadius = FVector::Distance(
      FocusPositionInCameraCoordinate,
      EarthTransformInCameraCoordinate.GetLocation());
  double CameraPositionRadius = CameraInECEFTransform.GetLocation().Length();

  FVector ScaleAxis =
      EarthTransformInCameraCoordinate.GetLocation().GetUnsafeNormal();

  FVector DeltaLocation =
      (Scale - 1) * ScaleAxis * (CameraPositionRadius - FocusPositionRadius);

  TArray<FTransform> Result;
  for (size_t i = 1; i <= Num; i++) {
    double ScaleValue = double(i) / double(Num) * (Scale - 1);

    FVector InterpolateDeltaLocation =
        ScaleValue * ScaleAxis * (CameraPositionRadius - FocusPositionRadius);

    // FVector InterpolateDeltaLocation = FMath::VInterpTo(
    //     FVector(0, 0, 0),
    //     DeltaLocation,
    //     sin(i * (DOUBLE_PI / 2 / (Num * 1.0))) /
    //         sin(DOUBLE_PI / 2) * 1.0,
    //     1.0);

    FTransform AfterScaleEarthTransformInCameraCoordinate =
        EarthTransformInCameraCoordinate;

    AfterScaleEarthTransformInCameraCoordinate.SetLocation(
        EarthTransformInCameraCoordinate.GetLocation() +
        InterpolateDeltaLocation);

    FVector AfterScaleCursorPositionInECEFCoordinate =
        AfterScaleEarthTransformInCameraCoordinate.InverseTransformPosition(
            CursorPositionInCameraCoordinate);

    FVector AfterScaleCursorDirectionInECEFCoordinate =
        AfterScaleEarthTransformInCameraCoordinate.InverseTransformVector(
            CursorDirectionInCameraCoordinate);

    FHitResult HitResultInECEF;
    if (!UMirrorCoordinatesBPFuncLibrary::LineTraceVirtualEarthInECEF(
            AVirtualEarthActor::GetDynamicVirtualEarth(
                FVector(FocusPositionRadius)),
            AfterScaleCursorPositionInECEFCoordinate,
            AfterScaleCursorPositionInECEFCoordinate +
                9999999999999 * AfterScaleCursorDirectionInECEFCoordinate,
            HitResultInECEF)) {
      return Result;
    }

    FVector AfterScaleFocusPositionInCameraCoordinate =
        AfterScaleEarthTransformInCameraCoordinate.Inverse()
            .InverseTransformPosition(HitResultInECEF.Location);

    FVector AfterScaleFocusPositionToEarthCenterDirectionInCameraCoordiante =
        (AfterScaleFocusPositionInCameraCoordinate -
         AfterScaleEarthTransformInCameraCoordinate.GetLocation())
            .GetUnsafeNormal();

    FQuat AfterScaleFocusPositionQuat = FQuat::FindBetween(
        BeforeScaleFocusPositionToEarthCenterDirectionInCameraCoordiante,
        AfterScaleFocusPositionToEarthCenterDirectionInCameraCoordiante);

    AfterScaleEarthTransformInCameraCoordinate.SetRotation(
        AfterScaleFocusPositionQuat *
        AfterScaleEarthTransformInCameraCoordinate.GetRotation());

    FTransform AfterScaleCameraTransformInECEFCoordinate =
        AfterScaleEarthTransformInCameraCoordinate.Inverse();

    Result.Add(AfterScaleCameraTransformInECEFCoordinate);
  }

  return Result;
}
