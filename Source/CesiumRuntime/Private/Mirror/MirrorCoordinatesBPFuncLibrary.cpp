#include "Mirror/MirrorCoordinatesBPFuncLibrary.h"
#include "CesiumGeoreference.h"
#include "CesiumWgs84Ellipsoid.h"
#include "Kismet/GameplayStatics.h"

UWorld* UMirrorCoordinatesBPFuncLibrary::World = nullptr;
FTransform UMirrorCoordinatesBPFuncLibrary::ENUToENUTransform(
    const FVector& ENULonLatH,
    const FTransform& Transform,
    const FVector& ToENULonLatH) {
  FTransform OriginENUTransform = ENUToECEFTransform(ENULonLatH, Transform);
  FTransform ToENUTransform = ENUToECEFTransform(ToENULonLatH, FTransform());
  return OriginENUTransform * ToENUTransform.Inverse();
}

FTransform UMirrorCoordinatesBPFuncLibrary::ENUToECEFTransform(
    const FVector& ENULonLatH,
    const FTransform& Transform) {
  FVector ENUOriginInECEF =
      UCesiumWgs84Ellipsoid::LongitudeLatitudeHeightToEarthCenteredEarthFixed(
          ENULonLatH);

  FVector ENUOriginUpAxis =
      UCesiumWgs84Ellipsoid::GeodeticSurfaceNormal(ENUOriginInECEF);

  FVector ENUOriginEastAxis = GetECEFEastAxisWithLonLatH(ENULonLatH);

  FVector ENUOriginNorthAxis = GetECEFNorthAxisWithLonLatH(ENULonLatH);

  FQuat ENUQuatInECEF = CalculateQuatFromAxes(
      ENUOriginEastAxis,
      ENUOriginNorthAxis,
      ENUOriginUpAxis);

  FTransform ECEFTransform;
  ECEFTransform.SetLocation(ENUOriginInECEF);
  ECEFTransform.SetRotation(ENUQuatInECEF);
  return Transform * ECEFTransform;
}

FTransform UMirrorCoordinatesBPFuncLibrary::ENUToUnrealTransform(
    const FVector& ENULonLatH,
    const FTransform& Transform) {
  FTransform ECEFTransform = ENUToECEFTransform(ENULonLatH, Transform);
  
  return ECEFTransform * GetECEFToUnrealTransform();
}

FTransform UMirrorCoordinatesBPFuncLibrary::ECEFToENUTransform(
    const FVector& ENULonLatH,
    const FTransform& Transform) {
  FTransform ENUECEFTransform = ENUToECEFTransform(ENULonLatH, FTransform());

  return Transform * ENUECEFTransform.Inverse();
}

FTransform UMirrorCoordinatesBPFuncLibrary::ECEFToUnrealTransform(
    const FTransform& Transform) {
  FTransform a = GetECEFToUnrealTransform();
  return Transform * a;
}

FTransform UMirrorCoordinatesBPFuncLibrary::UnrealToENUTransform(
    const FVector& ENULonLatH,
    const FTransform& Transform) {
  FTransform ECEFTransform = Transform * GetUnrealToECEFTransform();

  FTransform ENUECEFTransform = ENUToECEFTransform(ENULonLatH, FTransform());
  return ECEFTransform * ENUECEFTransform.Inverse();
}

FTransform UMirrorCoordinatesBPFuncLibrary::UnrealToECEFTransform(
    const FTransform& Transform) {
  return Transform * GetUnrealToECEFTransform();
}

FTransform UMirrorCoordinatesBPFuncLibrary::ENULookAt(
    const FVector& ENULonLatH,
    const FTransform& Transform,
    const FVector& LookAtLocation,
    double ArroundLookDirectionRotateAngle) {
  return FTransform();
}

FTransform UMirrorCoordinatesBPFuncLibrary::ECEFLookAt(
    const FTransform& Transform,
    const FVector& LookAtLocation,
    double ArroundLookDirectionRotateAngle) {
  return FTransform();
}

FTransform UMirrorCoordinatesBPFuncLibrary::UnrealLookAt(
    const FTransform& Transform,
    const FVector& LookAtLocation,
    double ArroundLookDirectionRotateAngle) {
  return FTransform();
}

FQuat UMirrorCoordinatesBPFuncLibrary::ArroundAxisRotation(
    const FVector& Axis,
    const double& Angle) {
  return FQuat(Axis, FMath::DegreesToRadians(Angle));
}

FVector UMirrorCoordinatesBPFuncLibrary::ENUToENULocation(
    const FVector& ENULonLatH,
    const FVector& ToENULonLatH,
    const FVector& Location) {
  return FVector();
}

FVector UMirrorCoordinatesBPFuncLibrary::ENUToECEFLocation(
    const FVector& ENULonLatH,
    const FVector& Location) {
  return FVector();
}

FVector UMirrorCoordinatesBPFuncLibrary::ENUToUnrealLocation(
    const FVector& ENULonLatH,
    const FVector& Location) {
  return FVector();
}

FVector UMirrorCoordinatesBPFuncLibrary::ECEFToENULocation(
    const FVector& ENULonLatH,
    const FVector& Location) {
  return FVector();
}

FVector
UMirrorCoordinatesBPFuncLibrary::ECEFToUnrealLocation(const FVector& Location) {
  return FVector();
}

FVector UMirrorCoordinatesBPFuncLibrary::UnrealToENULocation(
    const FVector& ENULonLatH,
    const FVector& Location) {
  return FVector();
}

FVector
UMirrorCoordinatesBPFuncLibrary::UnrealToECEFLocation(const FVector& Location) {
  return FVector();
}

FQuat UMirrorCoordinatesBPFuncLibrary::CalculateQuatFromAxes(
    const FVector& XAxis,
    const FVector& YAxis,
    const FVector& ZAxis) {
  check(
      FMath::IsNearlyEqual(FVector::DotProduct(XAxis, YAxis), 0, 0.00001) &&
      FMath::IsNearlyEqual(FVector::DotProduct(XAxis, ZAxis), 0, 0.00001) &&
      FMath::IsNearlyEqual(FVector::DotProduct(YAxis, ZAxis), 0, 0.00001));
  FMatrix Matrix = FMatrix(
      FPlane(XAxis.X, YAxis.X, ZAxis.X, 0),
      FPlane(XAxis.Y, YAxis.Y, ZAxis.Y, 0),
      FPlane(XAxis.Z, YAxis.Z, ZAxis.Z, 0),
      FPlane(0, 0, 0, 1));


  return Matrix.GetTransposed().ToQuat().GetNormalized();
}

FVector UMirrorCoordinatesBPFuncLibrary::GetECEFEastAxisWithLonLatH(
    const FVector& LonLatH) {
  return (UCesiumWgs84Ellipsoid::
             LongitudeLatitudeHeightToEarthCenteredEarthFixed(
                 LonLatH + FVector(0.000001, 0, 0)) -
         UCesiumWgs84Ellipsoid::
             LongitudeLatitudeHeightToEarthCenteredEarthFixed(
                 LonLatH )).GetUnsafeNormal();
}

FVector UMirrorCoordinatesBPFuncLibrary::GetECEFSouthAxisWithLonLatH(
    const FVector& LonLatH) {
  return (UCesiumWgs84Ellipsoid::
              LongitudeLatitudeHeightToEarthCenteredEarthFixed(
                  LonLatH + FVector(0, -0.000001, 0)) -
          UCesiumWgs84Ellipsoid::
              LongitudeLatitudeHeightToEarthCenteredEarthFixed(LonLatH))
      .GetUnsafeNormal();
}

FVector UMirrorCoordinatesBPFuncLibrary::GetECEFNorthAxisWithLonLatH(
    const FVector& LonLatH) {
  return (UCesiumWgs84Ellipsoid::
              LongitudeLatitudeHeightToEarthCenteredEarthFixed(
                  LonLatH + FVector(0, 0.000001, 0)) -
          UCesiumWgs84Ellipsoid::
              LongitudeLatitudeHeightToEarthCenteredEarthFixed(LonLatH))
      .GetUnsafeNormal();
}

FVector UMirrorCoordinatesBPFuncLibrary::GetECEFWestAxisWithLonLatH(
    const FVector& LonLatH) {
  return (UCesiumWgs84Ellipsoid::
              LongitudeLatitudeHeightToEarthCenteredEarthFixed(
                  LonLatH + FVector(-0.000001, 0, 0)) -
          UCesiumWgs84Ellipsoid::
              LongitudeLatitudeHeightToEarthCenteredEarthFixed(LonLatH))
      .GetUnsafeNormal();
}

FTransform UMirrorCoordinatesBPFuncLibrary::GetECEFToUnrealTransform() {
  return FTransform(ACesiumGeoreference::GetDefaultGeoreference(GWorld)
      ->ComputeEarthCenteredEarthFixedToUnrealTransformation());
}

FTransform UMirrorCoordinatesBPFuncLibrary::GetUnrealToECEFTransform() {
  return FTransform(ACesiumGeoreference::GetDefaultGeoreference(GWorld)->ComputeUnrealToEarthCenteredEarthFixedTransformation());
}

FHitResult UMirrorCoordinatesBPFuncLibrary::LineTraceVirtualEarthInECEF(
    AVirtualEarthActor* VirtualEarth,
    FVector Start,
    FVector End) {
  FHitResult result;
  FCollisionQueryParams Params;
  TArray<AActor*> Actors;
  UGameplayStatics::GetAllActorsOfClass(GWorld, AActor::StaticClass(), Actors);
  Actors.Remove(VirtualEarth);
  Params.AddIgnoredActors(Actors);
  GWorld->LineTraceSingleByChannel(
      result,
      Start * 100,
      End * 100,
      ECollisionChannel::ECC_GameTraceChannel3,
      Params);
  result.Location = result.Location / 100.0;
  result.Distance = result.Distance / 100.0;
  result.ImpactPoint = result.ImpactPoint / 100.0;
  result.TraceStart = Start;
  result.TraceEnd = End;
  return result;
}

FHitResult UMirrorCoordinatesBPFuncLibrary::LineTraceVirtualEarthInUnreal(
    AVirtualEarthActor* VirtualEarth,
    FVector Start,
    FVector End) {
  FTransform ECEFTransform = VirtualEarth->GetActorTransform();
  FTransform UnrealTransform = ECEFTransform * GetECEFToUnrealTransform();
  VirtualEarth->SetActorTransform(UnrealTransform);

  FHitResult result;
  FCollisionQueryParams Params;
  TArray<AActor*> Actors;
  UGameplayStatics::GetAllActorsOfClass(GWorld, AActor::StaticClass(), Actors);
  Actors.Remove(VirtualEarth);
  Params.AddIgnoredActors(Actors);
  GWorld->LineTraceSingleByChannel(
      result,
      Start,
      End,
      ECollisionChannel::ECC_GameTraceChannel3,
      Params);
  return result;
}

bool UMirrorCoordinatesBPFuncLibrary::ScreenToUnreal(
    APlayerController const* Player,
    FVector2D ScreenPosition,
    FVector& UnrealPosition,
    FVector& UnrealDirection) {
  return UGameplayStatics::DeprojectScreenToWorld(
      Player,
      ScreenPosition,
      UnrealPosition,
      UnrealDirection);
}

bool UMirrorCoordinatesBPFuncLibrary::UnrealToScreen(
    APlayerController const* Player,
    FVector UnrealPosition,
    FVector2D& ScreenPosition) {
  return UGameplayStatics::ProjectWorldToScreen(
      Player,
      UnrealPosition,
      ScreenPosition);
}

bool UMirrorCoordinatesBPFuncLibrary::ScreenToECEF(
    APlayerController const* Player,
    FVector2D ScreenPosition,
    FVector& ECEFPosition,
    FVector& ECEFDirection) {
  FVector UnrealPosition, UnrealDirection;
  if (!ScreenToUnreal(
          Player,
          ScreenPosition,
          UnrealPosition,
          UnrealDirection)) {
    return false;
  }
  ECEFPosition = GetUnrealToECEFTransform().TransformPosition(UnrealPosition);
  ECEFDirection = GetUnrealToECEFTransform()
                      .TransformVector(UnrealDirection)
                      .GetUnsafeNormal();
  return true;
}

bool UMirrorCoordinatesBPFuncLibrary::ECEFToScreen(
    APlayerController const* Player,
    FVector ECEFPosition,
    FVector2D& ScreenPosition) {
  FVector UnrealPosition = GetECEFToUnrealTransform().TransformPosition(ECEFPosition);
  return UnrealToScreen(Player, UnrealPosition, ScreenPosition);
}
