// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MirrorEarthManipulatorBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CESIUMRUNTIME_API UMirrorEarthManipulatorBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
        static TArray<FTransform> GetManipulatorMoveECEFTransform(
            const FTransform& CameraInECEFTransform,
            const FVector& EarthPositionInCameraCoordinate,
            const FVector& AfterMoveEarthPositionInCameraCoordinate,
            const int& Num);
};
