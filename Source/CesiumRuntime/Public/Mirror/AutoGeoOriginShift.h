// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CesiumGeoreference.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutoGeoOriginShift.generated.h"

UCLASS()
class CESIUMRUNTIME_API AAutoGeoOriginShift : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AAutoGeoOriginShift();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  UPROPERTY(EditAnywhere)
  bool AutoGeoOriginShiftEnable = false;

  UPROPERTY(EditAnywhere)
  ACesiumGeoreference* CesiumGeoreference = nullptr;

  UPROPERTY(EditAnywhere)
  unsigned int AutoShiftLevel = 10;

  UPROPERTY(EditAnywhere)
  bool firstTimeShift = true;

  UFUNCTION(BlueprintCallable)
  void SetAutoShiftGeoreference(ACesiumGeoreference* inGeoreference);

  UFUNCTION(BlueprintCallable)
  ACesiumGeoreference* GetAutoShiftGeoreference();

  virtual bool ShouldTickIfViewportsOnly() const override;

  UFUNCTION(BlueprintCallable)
  static AAutoGeoOriginShift*
  GetDefaultOriginShift(const UObject* WorldContextObject);

  DECLARE_MULTICAST_DELEGATE_OneParam(
      FGeoreferenceOriginChangeDelegate,
      const FTransform& /*new transform*/);
  FGeoreferenceOriginChangeDelegate GeoreferenceOriginChangeDelegate;

private:
  UPROPERTY(VisibleAnywhere)
  FVector ShiftOrigin;

  FVector CalAutoShiftOrigin();

  static FName DEFAULT_ORIGINSHIFT_TAG;
};
