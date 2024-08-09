#include "Mirror/MirrorCoordinatesBPFuncLibrary.h"
#include "CesiumGeoreference.h"
#include "CesiumWgs84Ellipsoid.h"
#include "Kismet/GameplayStatics.h"
#include <CesiumGeometry/BoundingSphere.h>
#include <CesiumGeospatial/GlobeTransforms.h>
#include <CesiumGeometry/OrientedBoundingBox.h>
#include <CesiumGeospatial/BoundingRegion.h>
#include <CesiumGeospatial/BoundingRegionWithLooseFittingHeights.h>
#include <CesiumGeospatial/S2CellBoundingVolume.h>
#include <Cesium3DTilesSelection/BoundingVolume.h>
#include <VecMath.h>
#include <Cesium3DTilesSelection/Tile.h>
#include "Cesium3DTileset.h"
UWorld* UMirrorCoordinatesBPFuncLibrary::World = nullptr;
FTransform UMirrorCoordinatesBPFuncLibrary::ESUToESUTransform(
    const FVector& ESULonLatH,
    const FTransform& Transform,
    const FVector& ToESULonLatH) {
  FTransform OriginESUTransform = ESUToECEFTransform(ESULonLatH, Transform);
  FTransform ToESUTransform = ESUToECEFTransform(ToESULonLatH, FTransform());
  return OriginESUTransform * ToESUTransform.Inverse();
}

FTransform UMirrorCoordinatesBPFuncLibrary::ESUToECEFTransform(
    const FVector& ESULonLatH,
    const FTransform& Transform) {
  FVector ESUOriginInECEF =
      UCesiumWgs84Ellipsoid::LongitudeLatitudeHeightToEarthCenteredEarthFixed(
          ESULonLatH);

  FVector ESUOriginUpAxis =
      UCesiumWgs84Ellipsoid::GeodeticSurfaceNormal(ESUOriginInECEF);

  FVector ESUOriginEastAxis = GetECEFEastAxisWithLonLatH(ESULonLatH);

  FVector ESUOriginNorthAxis = GetECEFNorthAxisWithLonLatH(ESULonLatH);

  FQuat ESUQuatInECEF = CalculateQuatFromAxes(
      ESUOriginEastAxis,
      ESUOriginNorthAxis,
      ESUOriginUpAxis);

  FTransform ENUToESUTransfrom;
  ENUToESUTransfrom.SetRotation(FRotator(0, 180, 0).Quaternion());
  ENUToESUTransfrom.SetScale3D(FVector(-1, 1, 1));
  

  FTransform ENUECEFTransform;
  ENUECEFTransform.SetLocation(ESUOriginInECEF);
  ENUECEFTransform.SetRotation(ESUQuatInECEF);
  return Transform * (ENUToESUTransfrom * ENUECEFTransform);
}

FTransform UMirrorCoordinatesBPFuncLibrary::ESUToUnrealTransform(
    const FVector& ESULonLatH,
    const FTransform& Transform) {
  FTransform ECEFTransform = ESUToECEFTransform(ESULonLatH, Transform);
  
  return ECEFTransform * GetECEFToUnrealTransform();
}

FTransform UMirrorCoordinatesBPFuncLibrary::ECEFToESUTransform(
    const FVector& ESULonLatH,
    const FTransform& Transform) {
  FTransform ESUECEFTransform = ESUToECEFTransform(ESULonLatH, FTransform());

  return Transform * ESUECEFTransform.Inverse();
}

FTransform UMirrorCoordinatesBPFuncLibrary::ECEFToUnrealTransform(
    const FTransform& Transform) {
  FTransform a = GetECEFToUnrealTransform();
  return Transform * a;
}

FTransform UMirrorCoordinatesBPFuncLibrary::UnrealToESUTransform(
    const FVector& ESULonLatH,
    const FTransform& Transform) {
  FTransform ECEFTransform = Transform * GetUnrealToECEFTransform();

  FTransform ESUECEFTransform = ESUToECEFTransform(ESULonLatH, FTransform());
  return ECEFTransform * ESUECEFTransform.Inverse();
}

FTransform UMirrorCoordinatesBPFuncLibrary::UnrealToECEFTransform(
    const FTransform& Transform) {
  return Transform * GetUnrealToECEFTransform();
}

FTransform UMirrorCoordinatesBPFuncLibrary::ESULookAt(
    const FVector& ESULonLatH,
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

FVector UMirrorCoordinatesBPFuncLibrary::ESUToESULocation(
    const FVector& ESULonLatH,
    const FVector& ToESULonLatH,
    const FVector& Location) {
  return FVector();
}

FVector UMirrorCoordinatesBPFuncLibrary::ESUToECEFLocation(
    const FVector& ESULonLatH,
    const FVector& Location) {
  FTransform ESUTransform;
  ESUTransform.SetLocation(Location);
  FTransform ECEFTransform = ESUToECEFTransform(ESULonLatH, ESUTransform);
  return ECEFTransform.GetLocation();
}

FVector UMirrorCoordinatesBPFuncLibrary::ESUToUnrealLocation(
    const FVector& ESULonLatH,
    const FVector& Location) {
  FTransform ESUTransform;
  ESUTransform.SetLocation(Location);
  FTransform UnrealTransform = ESUToUnrealTransform(ESULonLatH, ESUTransform);
  return UnrealTransform.GetLocation();
}

FVector UMirrorCoordinatesBPFuncLibrary::ECEFToESULocation(
    const FVector& ESULonLatH,
    const FVector& Location) {
  return ESUToECEFTransform(ESULonLatH, FTransform())
      .InverseTransformPosition(Location);
}

FVector
UMirrorCoordinatesBPFuncLibrary::ECEFToUnrealLocation(const FVector& Location) {
  return GetECEFToUnrealTransform().TransformPosition(Location);
}

FVector UMirrorCoordinatesBPFuncLibrary::UnrealToESULocation(
    const FVector& ESULonLatH,
    const FVector& Location) {
  return ECEFToESULocation(ESULonLatH, UnrealToECEFLocation(Location));
}

FVector
UMirrorCoordinatesBPFuncLibrary::UnrealToECEFLocation(const FVector& Location) {
  return GetUnrealToECEFTransform().TransformPosition(Location);
}

FQuat UMirrorCoordinatesBPFuncLibrary::CalculateQuatFromAxes(
    const FVector& XAxis,
    const FVector& YAxis,
    const FVector& ZAxis) {
  //check(
  //    FMath::IsNearlyEqual(FVector::DotProduct(XAxis, YAxis), 0, 0.00001) &&
  //    FMath::IsNearlyEqual(FVector::DotProduct(XAxis, ZAxis), 0, 0.00001) &&
  //    FMath::IsNearlyEqual(FVector::DotProduct(YAxis, ZAxis), 0, 0.00001));
  //bool bIsOrthogonal =
  //    (XAxis | YAxis) == 0 && (XAxis | ZAxis) == 0 && (YAxis | ZAxis) == 0;
  //bool bFollowsRightHandRule = (XAxis ^ YAxis) == ZAxis;
  //if (!bIsOrthogonal || !bFollowsRightHandRule) {
  //  UE_LOG(
  //      LogTemp,
  //      Error,
  //      TEXT("Axes do not form a valid orthogonal right-handed basis."));
  //  return FQuat::Identity; // Return identity quaternion as a fallback.
  //}

  FMatrix Matrix = FMatrix(
      FPlane(XAxis.X, YAxis.X, ZAxis.X, 0),
      FPlane(XAxis.Y, YAxis.Y, ZAxis.Y, 0),
      FPlane(XAxis.Z, YAxis.Z, ZAxis.Z, 0),
      FPlane(0, 0, 0, 1));
  FQuat Quat = Matrix.ToQuat().GetNormalized();

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

bool UMirrorCoordinatesBPFuncLibrary::LineTraceVirtualEarthInECEF(
    AVirtualEarthActor* VirtualEarth,
    FVector Start,
    FVector End,
    FHitResult& result) {
  FCollisionQueryParams Params;
  TArray<AActor*> Actors;
  UGameplayStatics::GetAllActorsOfClass(GWorld, AActor::StaticClass(), Actors);
  Actors.Remove(VirtualEarth);
  Params.AddIgnoredActors(Actors);
  bool bSuccessful = GWorld->LineTraceSingleByChannel(
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
  return bSuccessful;
}

bool UMirrorCoordinatesBPFuncLibrary::LineTraceVirtualEarthInUnreal(
    AVirtualEarthActor* VirtualEarth,
    FVector Start,
    FVector End,
    FHitResult& result) {
  FTransform ECEFTransform = VirtualEarth->GetActorTransform();
  FTransform UnrealTransform = ECEFTransform * GetECEFToUnrealTransform();
  VirtualEarth->SetActorTransform(UnrealTransform);

  FCollisionQueryParams Params;
  TArray<AActor*> Actors;
  UGameplayStatics::GetAllActorsOfClass(GWorld, AActor::StaticClass(), Actors);
  Actors.Remove(VirtualEarth);
  Params.AddIgnoredActors(Actors);
  bool bSuccessful = GWorld->LineTraceSingleByChannel(
      result,
      Start,
      End,
      ECollisionChannel::ECC_GameTraceChannel3,
      Params);
  return bSuccessful;
}

bool UMirrorCoordinatesBPFuncLibrary::LineTraceRealEarthInECEF(
    FVector Start,
    FVector End,
    FHitResult& result) {

  FVector UnrealStart = ECEFToUnrealLocation(Start);
  FVector UnrealEnd = ECEFToUnrealLocation(End);
  bool bSuccessful = LineTraceRealEarthInUnreal(
      ECEFToUnrealLocation(Start),
      ECEFToUnrealLocation(End),
      result);

  result.ImpactPoint = UnrealToECEFLocation(result.ImpactPoint);
  result.ImpactNormal =
      GetUnrealToECEFTransform().TransformVector(result.ImpactNormal);
  result.Location = UnrealToECEFLocation(result.Location);

  return bSuccessful;
}

bool UMirrorCoordinatesBPFuncLibrary::LineTraceRealEarthInUnreal(
    FVector Start,
    FVector End,
    FHitResult& HitResult) {
  return GWorld->LineTraceSingleByChannel(
      HitResult,
      Start,
      End,
      ECollisionChannel::ECC_Visibility);
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

FTransform
UMirrorCoordinatesBPFuncLibrary::GetViewUnrealTransform(const APawn* Pawn) {
  APlayerController* Controller =
      Cast<APlayerController>(Pawn->GetController());
  FTransform CameraInUnrealTransform;
  FVector Location;
  FRotator Rotation;
  Controller->GetPlayerViewPoint(Location, Rotation);
  CameraInUnrealTransform.SetLocation(Location);
  CameraInUnrealTransform.SetRotation(FQuat(Rotation));
  return CameraInUnrealTransform;
}

FTransform
UMirrorCoordinatesBPFuncLibrary::GetViewECEFTransform(const APawn* Pawn) {
  FTransform TransformNoScale =
      GetViewUnrealTransform(Pawn) * GetUnrealToECEFTransform();
  TransformNoScale.SetScale3D(FVector(1));
  return TransformNoScale;
}

FVector
UMirrorCoordinatesBPFuncLibrary::ECEFToLonLatH(const FVector& ECEFPosition) {
  return UCesiumWgs84Ellipsoid::EarthCenteredEarthFixedToLongitudeLatitudeHeight(
      ECEFPosition);
}

FVector UMirrorCoordinatesBPFuncLibrary::UnrealToLonLatH(
    const FVector& UnrealPosition) {
  FVector ECEFPosition = UnrealToECEFLocation(UnrealPosition);
  return ECEFToLonLatH(ECEFPosition);
}

FVector UMirrorCoordinatesBPFuncLibrary::LonLatHToECEF(const FVector& LonLatH) {
  return UCesiumWgs84Ellipsoid::
      LongitudeLatitudeHeightToEarthCenteredEarthFixed(LonLatH);
}

FVector
UMirrorCoordinatesBPFuncLibrary::LonLatHToUnreal(const FVector& LonLatH) {
  FVector ECEFPosition = LonLatHToECEF(LonLatH);
  return ECEFToUnrealLocation(ECEFPosition);
}

bool UMirrorCoordinatesBPFuncLibrary::IsInEditorMode() {
#if WITH_EDITOR
  return GIsEditor && !IsRunningGame();
#else
  return false;
#endif
}

bool UMirrorCoordinatesBPFuncLibrary::IsInEditorPlayMode() {
#if WITH_EDITOR
  return GIsEditor && GEditor->PlayWorld != nullptr;
#else
  return false;
#endif
}

void UMirrorCoordinatesBPFuncLibrary::GetCameraPosition(
    UWorld* World,
    FVector& OutLocation,
    FRotator& OutRotation) {
  if (IsInEditorMode() && !IsInEditorPlayMode()) {
#if WITH_EDITOR
    if (GEditor && GEditor->GetActiveViewport()) {
      FEditorViewportClient* EditorViewportClient =
          static_cast<FEditorViewportClient*>(
              GEditor->GetActiveViewport()->GetClient());

      if (EditorViewportClient) {
        OutLocation = EditorViewportClient->GetViewLocation();
        OutRotation = EditorViewportClient->GetViewRotation();
      }
    }
#endif
  } else if (IsInPlayMode() || IsInEditorPlayMode()) {
    if (World) {
      APlayerController* PlayerController =
          UGameplayStatics::GetPlayerController(World, 0);
      if (PlayerController) {
        if (PlayerController->GetPawn()) {
          APawn* PlayerPawn = PlayerController->GetPawn();
          OutLocation = PlayerPawn->GetActorLocation();
          OutRotation = PlayerPawn->GetActorRotation();
        } else if (PlayerController->PlayerCameraManager) {
          OutLocation =
              PlayerController->PlayerCameraManager->GetCameraLocation();
          OutRotation =
              PlayerController->PlayerCameraManager->GetCameraRotation();
        }
      }
    }
  }
}


FTransform UMirrorCoordinatesBPFuncLibrary::GetCameraTransform(UWorld* World) {
  FVector Location;
  FRotator Rotation;
  GetCameraPosition(World, Location, Rotation);
  FTransform result;
  result.SetLocation(Location);
  result.SetRotation(Rotation.Quaternion());
  return result;
}

FTransform
UMirrorCoordinatesBPFuncLibrary::GetFocusToCesium3DTilesetTransformInUnreal(
    ACesium3DTileset* Cesium3DTileset) {
  struct CalculateECEFCameraPosition {
    glm::dvec3 operator()(const CesiumGeometry::BoundingSphere& sphere) {
      const glm::dvec3& center = sphere.getCenter();
      glm::dmat4 ENU =
          CesiumGeospatial::GlobeTransforms::eastNorthUpToFixedFrame(center);
      glm::dvec3 offset =
          sphere.getRadius() *
          glm::normalize(
              glm::dvec3(ENU[0]) + glm::dvec3(ENU[1]) + glm::dvec3(ENU[2]));
      glm::dvec3 position = center + offset;
      return position;
    }

    glm::dvec3
    operator()(const CesiumGeometry::OrientedBoundingBox& orientedBoundingBox) {
      const glm::dvec3& center = orientedBoundingBox.getCenter();
      glm::dmat4 ENU =
          CesiumGeospatial::GlobeTransforms::eastNorthUpToFixedFrame(center);
      const glm::dmat3& halfAxes = orientedBoundingBox.getHalfAxes();
      glm::dvec3 offset =
          glm::length(halfAxes[0] + halfAxes[1] + halfAxes[2]) *
          glm::normalize(
              glm::dvec3(ENU[0]) + glm::dvec3(ENU[1]) + glm::dvec3(ENU[2]));
      glm::dvec3 position = center + offset;
      return position;
    }

    glm::dvec3
    operator()(const CesiumGeospatial::BoundingRegion& boundingRegion) {
      return (*this)(boundingRegion.getBoundingBox());
    }

    glm::dvec3
    operator()(const CesiumGeospatial::BoundingRegionWithLooseFittingHeights&
                   boundingRegionWithLooseFittingHeights) {
      return (*this)(boundingRegionWithLooseFittingHeights.getBoundingRegion()
                         .getBoundingBox());
    }

    glm::dvec3 operator()(const CesiumGeospatial::S2CellBoundingVolume& s2) {
      return (*this)(s2.computeBoundingRegion());
    }
  };

  const Cesium3DTilesSelection::Tile* pRootTile =
      Cesium3DTileset->GetTileset()->getRootTile();
  if (!pRootTile) {
    return FTransform();
  }

  const Cesium3DTilesSelection::BoundingVolume& boundingVolume =
      pRootTile->getBoundingVolume();

  ACesiumGeoreference* pGeoreference = Cesium3DTileset->ResolveGeoreference();

  // calculate unreal camera position
  glm::dvec3 ecefCameraPosition =
      std::visit(CalculateECEFCameraPosition{}, boundingVolume);
  FVector unrealCameraPosition =
      pGeoreference->TransformEarthCenteredEarthFixedPositionToUnreal(
          VecMath::createVector(ecefCameraPosition));

  // calculate unreal camera orientation
  glm::dvec3 ecefCenter =
      Cesium3DTilesSelection::getBoundingVolumeCenter(boundingVolume);
  FVector unrealCenter =
      pGeoreference->TransformEarthCenteredEarthFixedPositionToUnreal(
          VecMath::createVector(ecefCenter));
  FVector unrealCameraFront =
      (unrealCenter - unrealCameraPosition).GetSafeNormal();
  FVector unrealCameraRight =
      FVector::CrossProduct(FVector::ZAxisVector, unrealCameraFront)
          .GetSafeNormal();
  FVector unrealCameraUp =
      FVector::CrossProduct(unrealCameraFront, unrealCameraRight)
          .GetSafeNormal();
  FRotator cameraRotator = FMatrix(
                               unrealCameraFront,
                               unrealCameraRight,
                               unrealCameraUp,
                               FVector::ZeroVector)
                               .Rotator();
  FTransform result;
  result.SetLocation(unrealCameraPosition);
  result.SetRotation(cameraRotator.Quaternion());
  return result;
}

bool UMirrorCoordinatesBPFuncLibrary::IsInPlayMode() {
   return !GIsEditor || IsRunningGame(); 
}

