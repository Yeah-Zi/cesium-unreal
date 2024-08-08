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
        FMath::Clamp<double>(
            sin(i * (DOUBLE_PI / 2 / (Num * 1.0))) / sin(DOUBLE_PI / 2) * 1.0,
            0.f,
            1.f));

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

     //FVector InterpolateDeltaLocation = FMath::VInterpTo(
     //    FVector(0, 0, 0),
     //    DeltaLocation,
     //    sin(i * (DOUBLE_PI / 2 / (Num * 1.0))) /
     //        sin(DOUBLE_PI / 2) * 1.0,
     //    1.0);

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

double IncludedAngle(
    const FVector& StartPointEarthLocation,
    const FVector& TargetPointEarthLocation) {
  double LStart = sqrt(
      pow(StartPointEarthLocation.X, 2) + pow(StartPointEarthLocation.Y, 2) +
      pow(StartPointEarthLocation.Z, 2));
  double LTarget = sqrt(
      pow(TargetPointEarthLocation.X, 2) + pow(TargetPointEarthLocation.Y, 2) +
      pow(TargetPointEarthLocation.Z, 2));
  double CosTheta =
      (StartPointEarthLocation | TargetPointEarthLocation) / (LStart * LTarget);
  if (abs(CosTheta) > 1) {
    CosTheta = CosTheta / abs(CosTheta);
  }
  double Theta = acos(CosTheta);

  return Theta;
}

double AngleD(const FVector& a, const FVector& b) {
  return FQuat::FindBetween(a.GetSafeNormal(), b.GetSafeNormal()).GetAngle() *
         180.0 / DOUBLE_PI;
}

TArray<FTransform>
UMirrorEarthManipulatorBPLibrary::GetManipulatorRotateECEFTransform(
    const FTransform& CameraInECEFTransform,
    const FVector FocusPointInECEFCoordinate,
    double yawDegree,
    double PitchDegree,
    const int& Num) {

  FVector CameraToFocusDirection =
      (CameraInECEFTransform.GetLocation() - FocusPointInECEFCoordinate)
          .GetUnsafeNormal();

  FPlane CameraPlane(CameraInECEFTransform.GetRotation().GetAxisY(), 0);

  double Min, Max;
  {
    FVector ProjectCameraAxisX = FPlane::PointPlaneProject(
        CameraInECEFTransform.GetRotation().GetAxisX(),
        CameraPlane);

    FVector ProjectCameraLocation = FPlane::PointPlaneProject(
        CameraInECEFTransform.GetLocation().GetUnsafeNormal(),
        CameraPlane);

    double maxPitchDegree =
        FQuat::FindBetween(ProjectCameraAxisX, ProjectCameraLocation)
                .GetAngle() *
            180.0 / PI -
        0;
    maxPitchDegree = maxPitchDegree < 0 ? 0 : maxPitchDegree;
    double minPitchDegree = maxPitchDegree - 90 + 0;

    double temp = minPitchDegree;
    minPitchDegree = -maxPitchDegree;
    maxPitchDegree = -temp - 10;
    Min = minPitchDegree;
    Max = maxPitchDegree;
  }




  {
    FVector ProjectCameraToFocusDirection = FPlane::PointPlaneProject(CameraToFocusDirection,
        CameraPlane);

    FVector ProjectFocusPointInECEFCoordinate = FPlane::PointPlaneProject(
        FocusPointInECEFCoordinate.GetUnsafeNormal(),
        CameraPlane);

    double maxPitchDegree = FQuat::FindBetween(
                                ProjectCameraToFocusDirection,
                                ProjectFocusPointInECEFCoordinate)
                                    .GetAngle() *
                                180.0 / PI -
                            0;
    maxPitchDegree = maxPitchDegree < 0 ? 0 : maxPitchDegree;
    double minPitchDegree = maxPitchDegree - 90 + 0;

    double temp = minPitchDegree;
    minPitchDegree = -maxPitchDegree;
    maxPitchDegree = -temp - 10;

    Max = Max > maxPitchDegree ? maxPitchDegree : Max;
  }



   PitchDegree = FMath::Clamp(PitchDegree, Min, Max);






  TArray<FTransform> Result;
	for (size_t i = 1; i <= Num; i++) {
    double interpolatePitchDegree = double(i) / double(Num) * PitchDegree;
    double interpolateYawDegree = double(i) / double(Num) * yawDegree;

    FVector pitchAxis = CameraInECEFTransform.GetRotation().GetAxisY();
    FVector localCameraLocation =
        CameraInECEFTransform.GetLocation() - FocusPointInECEFCoordinate;
    FQuat pitchRotateMat; //  EMath::AroundAxisRotation(UnitAxis, RotateDegree);
    pitchRotateMat = FQuat(UMirrorCoordinatesBPFuncLibrary::ArroundAxisRotation(
            pitchAxis,
            interpolatePitchDegree));
    localCameraLocation = pitchRotateMat * localCameraLocation;
    FQuat afterPitchCameraRotate =
        pitchRotateMat * CameraInECEFTransform.GetRotation();

    FVector yawAxis = FocusPointInECEFCoordinate.GetUnsafeNormal();
    FQuat yawRotateMat; //  EMath::AroundAxisRotation(UnitAxis, RotateDegree);
    yawRotateMat = FQuat(UMirrorCoordinatesBPFuncLibrary::ArroundAxisRotation(
        yawAxis,
        interpolateYawDegree));
    localCameraLocation = yawRotateMat * localCameraLocation;
    FQuat afterYawCameraRotate = yawRotateMat * afterPitchCameraRotate;

    FTransform interpolateCameraTransform;
    interpolateCameraTransform.SetTranslation(
        localCameraLocation + FocusPointInECEFCoordinate);
    interpolateCameraTransform.SetRotation(afterYawCameraRotate);
    Result.Add(interpolateCameraTransform);
  }

  return Result;
}

TArray<FTransform>
UMirrorEarthManipulatorBPLibrary::GetManipulatorRotateECEFTransform2(
    const FTransform& CameraInECEFTransform,
    const FVector focalPointInSphereCoordinate,
    double yawDegree,
    double pitchDegree,
    const int& tickCount) {
  TArray<FTransform> resultTransform;

  FTransform CameraInECEF = CameraInECEFTransform;
  FVector cameraLocation = CameraInECEF.GetLocation();
  FQuat cameraRotation = FQuat(CameraInECEF.GetRotation());

  FVector cameraToFocalNormal =
      (cameraLocation - focalPointInSphereCoordinate).GetSafeNormal();

  // 计算轴点与球心的球向量在球心沿Y轴方向上的投影，P0为投影点
  FVector V1 = focalPointInSphereCoordinate;
  FVector V2 = cameraRotation.GetAxisY();
  double LV1 = sqrt(pow(V1.X, 2) + pow(V1.Y, 2) + pow(V1.Z, 2));
  double K = cos(IncludedAngle(V1, V2)) * LV1;
  FVector P0 = V2 * K;

  FPlane plane((FVector)cameraRotation.GetAxisY(), 0);
  FVector targetDiretion = FVector::CrossProduct(
      cameraRotation.GetAxisY(),
      (focalPointInSphereCoordinate).GetSafeNormal());
  double maxPitchDegree =
      AngleD(cameraRotation.GetAxisX(), cameraLocation.GetUnsafeNormal()) - 2;
  maxPitchDegree = maxPitchDegree < 0 ? 0 : maxPitchDegree; 
  double minPitchDegree = maxPitchDegree - 90 + 5;

  double temp = minPitchDegree;
  minPitchDegree = -maxPitchDegree;
  maxPitchDegree = -temp;


  pitchDegree = FMath::Clamp(pitchDegree, minPitchDegree, maxPitchDegree);

      GEngine->AddOnScreenDebugMessage(
      -1,
      4,
      FColor::Red,
      FString("maxPitchDegree:") + FString::SanitizeFloat(maxPitchDegree));   
      GEngine->AddOnScreenDebugMessage(
          -1,
          4,
          FColor::Red,
          FString("minPitchDegree:") + FString::SanitizeFloat(minPitchDegree));   
  for (size_t i = 1; i <= tickCount; i++) {
    double interpolatePitchDegree = double(i) / double(tickCount) * pitchDegree;
    double interpolateYawDegree = double(i) / double(tickCount) * yawDegree;

    FVector pitchAxis = cameraRotation.GetAxisY();
    FVector localCameraLocation = cameraLocation - focalPointInSphereCoordinate;
    FQuat pitchRotateMat; //  EMath::AroundAxisRotation(UnitAxis, RotateDegree);
    pitchRotateMat = FQuat(UMirrorCoordinatesBPFuncLibrary::ArroundAxisRotation(
            pitchAxis,
            interpolatePitchDegree));
    localCameraLocation = pitchRotateMat * localCameraLocation;
    FQuat afterPitchCameraRotate = pitchRotateMat * cameraRotation;

    FVector yawAxis = focalPointInSphereCoordinate.GetSafeNormal();
    FQuat yawRotateMat; //  EMath::AroundAxisRotation(UnitAxis, RotateDegree);
    yawRotateMat = FQuat(UMirrorCoordinatesBPFuncLibrary::ArroundAxisRotation(
        yawAxis,
        interpolateYawDegree));
    localCameraLocation = yawRotateMat * localCameraLocation;
    FQuat afterYawCameraRotate = yawRotateMat * afterPitchCameraRotate;

    FTransform interpolateCameraTransform;
    interpolateCameraTransform.SetTranslation(
        localCameraLocation + focalPointInSphereCoordinate);
    interpolateCameraTransform.SetRotation(afterYawCameraRotate);
    resultTransform.Add(interpolateCameraTransform);
  }

  return resultTransform;
}

TArray<FTransform>
UMirrorEarthManipulatorBPLibrary::GetManipulatorThrowECEFTransform(
    const FTransform& CameraInECEFTransform,
    const FVector& EarthPositionInCameraCoordinate,
    const FVector& AfterMoveEarthPositionInCameraCoordinate,
    const int& Num,
    double& SuggestTime) {

  FTransform EarthTransformInCameraCoordinate = CameraInECEFTransform.Inverse();

  FVector EarthPositionToEarthCenterDirection =
      EarthPositionInCameraCoordinate - EarthTransformInCameraCoordinate.GetLocation();

  FVector AfterMoveEarthPositionToEarthCenterDirection =
      AfterMoveEarthPositionInCameraCoordinate -
      EarthTransformInCameraCoordinate.GetLocation();

  FQuat BeforeToAfterDirectionQuat = FQuat::FindBetween(
      EarthPositionToEarthCenterDirection,
      AfterMoveEarthPositionToEarthCenterDirection);


  // 不使用BeforeToAfterDirectionQuat.GetRotationAxis()， 精度丢失
  FVector axis = FVector(
      BeforeToAfterDirectionQuat.X,
      BeforeToAfterDirectionQuat.Y,
                     BeforeToAfterDirectionQuat.Z) /
                 FMath::Sqrt(
                     FMath::Pow(BeforeToAfterDirectionQuat.X, 2) +
                     FMath::Pow(BeforeToAfterDirectionQuat.Y, 2) +
                     FMath::Pow(BeforeToAfterDirectionQuat.Z, 2));

  FQuat ThrowQuat = FQuat(
      axis,
      BeforeToAfterDirectionQuat.GetAngle() * 7 >= PI
          ? (PI - 0.01)
          : BeforeToAfterDirectionQuat.GetAngle() * 7 );

  FVector AfterThrowEarthPositionInCameraCoordinate =
      ThrowQuat * EarthPositionToEarthCenterDirection +
      EarthTransformInCameraCoordinate.GetLocation();

  double ThrowDegree = ThrowQuat.GetAngle() * 180.0 / PI;
  SuggestTime =
      ((120 * ThrowDegree / 180) > 120 ? (120 * ThrowDegree / 180) : 120) / 60;

  return GetManipulatorMoveECEFTransform(
      CameraInECEFTransform,
      EarthPositionInCameraCoordinate,
      AfterThrowEarthPositionInCameraCoordinate,
      Num);
}
