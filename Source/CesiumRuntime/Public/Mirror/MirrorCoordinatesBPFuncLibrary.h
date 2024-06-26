// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VirtualEarthActor.h"
#if WITH_EDITOR
#include "Editor.h"
#include "Editor/UnrealEd/Public/EditorViewportClient.h"
#include "Editor/UnrealEd/Public/LevelEditorViewport.h"
#include "Engine/Engine.h"
#endif
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "MirrorCoordinatesBPFuncLibrary.generated.h"

USTRUCT()
struct CESIUMRUNTIME_API FGeographicCoordinateGesture {
  GENERATED_BODY()

  FVector LonLatH;
  FRotator Rotator;
  FVector Scale;
};

/**
 * now we have Coordinate Include {ENU, ECEF, Unreal}
 */
UCLASS()
class CESIUMRUNTIME_API UMirrorCoordinatesBPFuncLibrary
    : public UBlueprintFunctionLibrary {
  GENERATED_BODY()
public:
  static UWorld* World;

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform ENUToENUTransform(
      const FVector& ENULonLatH,
      const FTransform& Transform,
      const FVector& ToENULonLatH);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform
  ENUToECEFTransform(const FVector& ENULonLatH, const FTransform& Transform);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform
  ENUToUnrealTransform(const FVector& ENULonLatH, const FTransform& Transform);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform
  ECEFToENUTransform(const FVector& ENULonLatH, const FTransform& Transform);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform ECEFToUnrealTransform(const FTransform& Transform);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform
  UnrealToENUTransform(const FVector& ENULonLatH, const FTransform& Transform);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform UnrealToECEFTransform(const FTransform& Transform);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform ENULookAt(
      const FVector& LonLatH,
      const FTransform& Transform,
      const FVector& LookAtLocation,
      double ArroundLookDirectionRotateAngle = 0);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform ECEFLookAt(
      const FTransform& Transform,
      const FVector& LookAtLocation,
      double ArroundLookDirectionRotateAngle = 0);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform UnrealLookAt(
      const FTransform& Transform,
      const FVector& LookAtLocation,
      double ArroundLookDirectionRotateAngle = 0);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FQuat ArroundAxisRotation(const FVector& Axis, const double& Angle);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector ENUToENULocation(
      const FVector& ENULonLatH,
      const FVector& ToENULonLatH,
      const FVector& Location);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector
  ENUToECEFLocation(const FVector& ENULonLatH, const FVector& Location);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector
  ENUToUnrealLocation(const FVector& ENULonLatH, const FVector& Location);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector
  ECEFToENULocation(const FVector& ENULonLatH, const FVector& Location);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector ECEFToUnrealLocation(const FVector& Location);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector
  UnrealToENULocation(const FVector& ENULonLatH, const FVector& Location);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector UnrealToECEFLocation(const FVector& Location);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FQuat CalculateQuatFromAxes(
      const FVector& XAxis,
      const FVector& YAxis,
      const FVector& ZAxis);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector GetECEFEastAxisWithLonLatH(const FVector& LonLatH);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector GetECEFSouthAxisWithLonLatH(const FVector& LonLatH);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector GetECEFNorthAxisWithLonLatH(const FVector& LonLatH);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector GetECEFWestAxisWithLonLatH(const FVector& LonLatH);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform GetECEFToUnrealTransform();

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform GetUnrealToECEFTransform();

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static bool LineTraceVirtualEarthInECEF(
      AVirtualEarthActor* VirtualEarth,
      FVector Start,
      FVector End,
      FHitResult& result);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static bool LineTraceVirtualEarthInUnreal(
      AVirtualEarthActor* VirtualEarth,
      FVector Start,
      FVector End,
      FHitResult& result);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static bool
  LineTraceRealEarthInECEF(FVector Start, FVector End, FHitResult& result);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static bool
  LineTraceRealEarthInUnreal(FVector Start, FVector End, FHitResult& HitResult);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static bool ScreenToUnreal(
      APlayerController const* Player,
      FVector2D ScreenPosition,
      FVector& UnrealPosition,
      FVector& UnrealDirection);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static bool UnrealToScreen(
      APlayerController const* Player,
      FVector UnrealPosition,
      FVector2D& ScreenPosition);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static bool ScreenToECEF(
      APlayerController const* Player,
      FVector2D ScreenPosition,
      FVector& ECEFPosition,
      FVector& ECEFDirection);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static bool ECEFToScreen(
      APlayerController const* Player,
      FVector ECEFPosition,
      FVector2D& ScreenPosition);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform GetViewUnrealTransform(const APawn* Pawn);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform GetViewECEFTransform(const APawn* Pawn);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector ECEFToLonLatH(const FVector& ECEFPosition);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector UnrealToLonLatH(const FVector& UnrealPosition);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector LonLatHToECEF(const FVector& LonLatH);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FVector LonLatHToUnreal(const FVector& LonLatH);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static bool IsInEditorMode();

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static bool IsInEditorPlayMode();

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static bool IsInPlayMode();

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static void
  GetCameraPosition(UWorld* World, FVector& OutLocation, FRotator& OutRotation);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static FTransform GetCameraTransform(UWorld* World);
};
