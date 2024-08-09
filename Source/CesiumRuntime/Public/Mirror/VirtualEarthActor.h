// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "VirtualEarthActor.generated.h"

/**
 *
 */
UCLASS()
class CESIUMRUNTIME_API AVirtualEarthActor : public AStaticMeshActor {
  GENERATED_BODY()
public:
  AVirtualEarthActor();

  /* unit： meter*/
  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  void SetVirtualEarthRadii(const FVector& Radius);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static AVirtualEarthActor*
  GetWGS84VirtualEarth(UObject* WorldContextObject);

  UFUNCTION(
      BlueprintCallable,
      Category = "Coordinates",
      meta = (BlueprintAutocast))
  static AVirtualEarthActor*
  GetDynamicVirtualEarth(UObject* WorldContextObject, const FVector& Radius);

  protected:
   virtual void BeginDestroy() override;
};
