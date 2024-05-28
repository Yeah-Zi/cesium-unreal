// Fill out your copyright notice in the Description page of Project Settings.

#include "Mirror/MirrorMoveManagerComponent.h"
#include "CesiumGeoreference.h"
#include "Mirror/MirrorCoordinatesBPFuncLibrary.h"
// Sets default values for this component's properties
UMirrorMoveManagerComponent::UMirrorMoveManagerComponent() {
  // Set this component to be initialized when the game starts, and to be ticked
  // every frame.  You can turn these features off to improve performance if you
  // don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...
}

// Called when the game starts
void UMirrorMoveManagerComponent::BeginPlay() {
  Super::BeginPlay();

  // ...
}

// Called every frame
void UMirrorMoveManagerComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  UsedTime += DeltaTime;
  Move(UsedTime);
  // ...
}

void UMirrorMoveManagerComponent::SetActorTransforms(
    EMirrorCoordinate Coordinate,
    TArray<FTransform> Transforms,
    const double& InMoveTime,
    FCallbackScriptDelegate StartCallBack,
    FCallbackScriptDelegate StopCallBack,
    FCallbackScriptDelegate EndCallBack) {

  check(Coordinate != EMirrorCoordinate::ENU);

  for (size_t i = 0; i < Transforms.Num(); i++) {
    if (Coordinate == EMirrorCoordinate::UNREAL) {
      Transforms[i] =
          UMirrorCoordinatesBPFuncLibrary::UnrealToECEFTransform(Transforms[i]);
    } else if (Coordinate == EMirrorCoordinate::ECEF) {
      continue;
    }
  }
  if (!ECEFMoveInfos.isEnd && !ECEFMoveInfos.isStop) {
    ECEFMoveInfos.StopCallback();
  }
  ECEFMoveInfos = FMoveInfos();
  ECEFMoveInfos.Transforms = Transforms;
  ECEFMoveInfos.MoveTime = InMoveTime;
  ECEFMoveInfos.startCallback = StartCallBack;
  ECEFMoveInfos.stopCallback = StopCallBack;
  ECEFMoveInfos.endCallback = EndCallBack;
  UsedTime = 0;
}

void UMirrorMoveManagerComponent::AddActorTransforms(
    EMirrorCoordinate Coordinate,
    TArray<FTransform> Transforms,
    const double& InMoveTime) {
  check(Coordinate != EMirrorCoordinate::ENU);

  for (size_t i = 0; i < Transforms.Num(); i++) {
    if (Coordinate == EMirrorCoordinate::UNREAL) {
      Transforms[i] =
          UMirrorCoordinatesBPFuncLibrary::UnrealToECEFTransform(Transforms[i]);
    } else if (Coordinate == EMirrorCoordinate::ECEF) {
      continue;
    }
  }

  ECEFMoveInfos.MoveTime = ECEFMoveInfos.MoveTime + InMoveTime;
  ECEFMoveInfos.Transforms.Append(Transforms);
}

FMoveInfos UMirrorMoveManagerComponent::GetFMoveInfos() {
  return ECEFMoveInfos;
}

void UMirrorMoveManagerComponent::Move(const double& Time) {

  if (!ECEFMoveInfos.isStart) {
    ECEFMoveInfos.StartCallback();
  }

  if (ECEFMoveInfos.isStop || ECEFMoveInfos.isEnd) {
    return;
  }

  if (ECEFMoveInfos.Transforms.IsEmpty()) {
    ECEFMoveInfos.EndCallback();
    return;
  }
  GEngine->AddOnScreenDebugMessage(
      -1,
      1,
      FColor::Red,
      FString::SanitizeFloat(Time));
  int MoveIndex = FMath::Clamp(
      FMath::Clamp((Time / ECEFMoveInfos.MoveTime), 0.0, 1.0) *
          ECEFMoveInfos.Transforms.Num(),
      0,
      ECEFMoveInfos.Transforms.Num() - 1);

  FTransform InUnrealTransform =
      UMirrorCoordinatesBPFuncLibrary::ECEFToUnrealTransform(
          ECEFMoveInfos.Transforms[MoveIndex]);
  this->GetOwner()->SetActorTransform(InUnrealTransform);
  this->GetOwner()->UpdateComponentTransforms();

  if (MoveIndex == ECEFMoveInfos.Transforms.Num() - 1) {
    ECEFMoveInfos.EndCallback();
  }
}
