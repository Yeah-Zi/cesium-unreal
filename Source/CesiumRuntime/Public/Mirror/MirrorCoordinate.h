// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMirrorCoordinate : uint8 {
  UNREAL UMETA(DisplayName = "Unreal Coordinate"),

  ECEF UMETA(DisplayName = "ECEF Coordinate"),

  ENU UMETA(DisplayName = "ENU Coordinate")
};
