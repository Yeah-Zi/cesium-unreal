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

        static TArray<FTransform> GetManipulatorScaleECEFTransform(
            const FTransform& CameraInECEFTransform,
            const FVector& FocusPositionInCameraCoordinate,
            const FVector& CursorPositionInCameraCoordinate,
            const FVector& CursorDirectionInCameraCoordinate,
            const double& Scale,
            const int& Num);

        static TArray<FTransform> GetManipulatorRotateECEFTransform(
            const FTransform& CameraInECEFTransform,
            const FVector FocusPointInECEFCoordinate,
            double yawDegree,
            double PitchDegree,
            const int& Num);

        static TArray<FTransform> GetManipulatorRotateECEFTransform2(
            const FTransform& CameraInECEFTransform,
            const FVector focalPointInSphereCoordinate,
            double yawDegree,
            double pitchDegree,
            const int& tickCount);

        static TArray<FTransform> GetManipulatorThrowECEFTransform(
            const FTransform& CameraInECEFTransform,
            const FVector& EarthPositionInCameraCoordinate,
            const FVector& AfterMoveEarthPositionInCameraCoordinate,
            const int& Num,
            double& SuggestTime);
};
