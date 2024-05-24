// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "MirrorCoordinate.h"
#include "MirrorMoveManagerComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE(FCallbackScriptDelegate);


USTRUCT()
struct CESIUMRUNTIME_API FMoveInfos {
  GENERATED_BODY()
public:
  FMoveInfos(
      float inUseTime,
      TArray<FTransform> inInterpolateTransforms,
      int32 inPriority,
      FCallbackScriptDelegate inStartCallback,
      FCallbackScriptDelegate inStopCallback,
      FCallbackScriptDelegate inEndCallback)
      : startCallback(std::move(inStartCallback)),
        stopCallback(std::move(inStopCallback)),
        endCallback(std::move(inEndCallback)),
        MoveTime(inUseTime),
        Transforms(inInterpolateTransforms),
        priority(inPriority){};
  FMoveInfos() {
    MoveTime = 0;
    startCallback;
    stopCallback;
    endCallback;
  };

  float MoveTime;
  TArray<FTransform> Transforms;
  int32 priority = -1;
  bool isStart = false;
  bool isStop = false;
  bool isEnd = false;
  FCallbackScriptDelegate startCallback;
  FCallbackScriptDelegate stopCallback;
  FCallbackScriptDelegate endCallback;
  EMirrorCoordinate coordEnum = EMirrorCoordinate::ECEF;
  void StartCallback() {
    isStart = true;
    startCallback.ExecuteIfBound();
  };
  void StopCallback() {
    isStop = true;
    stopCallback.ExecuteIfBound();
  };
  void EndCallback() {
    isEnd = true;
    endCallback.ExecuteIfBound();
  };
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CESIUMRUNTIME_API UMirrorMoveManagerComponent : public UActorComponent {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UMirrorMoveManagerComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

  UPROPERTY()
  double UsedTime = 0;

public:
  // Called every frame
  virtual void TickComponent(
      float DeltaTime,
      ELevelTick TickType,
      FActorComponentTickFunction* ThisTickFunction) override;

  UPROPERTY()
  FMoveInfos ECEFMoveInfos;


  UFUNCTION()
  void SetActorTransforms(
      EMirrorCoordinate Coordinate,
      TArray<FTransform> Transforms,
      FCallbackScriptDelegate StartCallBack,
      FCallbackScriptDelegate StopCallBack,
      FCallbackScriptDelegate EndCallBack,
      const double& InMoveTime);

  UFUNCTION()
  void AddActorTransforms(
      EMirrorCoordinate Coordinate,
      TArray<FTransform> Transforms,
      const double& InMoveTime);

  FMoveInfos GetFMoveInfos();

  void Move(const double& Time);
};
