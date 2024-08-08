// Fill out your copyright notice in the Description page of Project Settings.


#include "Mirror/VirtualEarthActor.h"
#include "Components/StaticMeshComponent.h"
#include "CesiumWgs84Ellipsoid.h"
#include "Engine/StaticMesh.h"
#include "PhysicsEngine/BodySetup.h"

AVirtualEarthActor::AVirtualEarthActor() {
  //GetStaticMeshComponent()->SetCollisionResponseToChannel(ECollisionChannel::)
  GetStaticMeshComponent()->SetCollisionProfileName(FName("VirtualEarth"));
  GetStaticMeshComponent()->SetStaticMesh(
      LoadObject<UStaticMesh>(GetStaticMeshComponent(), TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")));
  GetStaticMeshComponent()->SetCollisionResponseToAllChannels(
      ECollisionResponse::ECR_Ignore);
  GetStaticMeshComponent()->SetCollisionResponseToChannel(
      ECollisionChannel::ECC_GameTraceChannel3,
      ECollisionResponse::ECR_Block);
  GetStaticMeshComponent()
      ->GetStaticMesh()
      ->GetBodySetup()
      ->bDoubleSidedGeometry = true;
  GetStaticMeshComponent()->SetVisibility(false);
  SetVirtualEarthRadii(UCesiumWgs84Ellipsoid::GetRadii());
}

void AVirtualEarthActor::SetVirtualEarthRadii(const FVector& Radius) {
  this->SetActorScale3D(FVector(2 * Radius));
}

AVirtualEarthActor* AVirtualEarthActor::GetWGS84VirtualEarth() {
  static AVirtualEarthActor* WGS84 = nullptr;
  if (!IsValid(WGS84)) {
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    WGS84 = GWorld->SpawnActor<AVirtualEarthActor>(Params);
    WGS84->SetActorLabel("WGS84VirtualEarth");
    WGS84->AddToRoot();
  }
  WGS84->SetVirtualEarthRadii(UCesiumWgs84Ellipsoid::GetRadii());
  return WGS84;
}

AVirtualEarthActor*
AVirtualEarthActor::GetDynamicVirtualEarth(const FVector& Radius) {
  static AVirtualEarthActor* VirtualEarth = nullptr;
  if (!IsValid(VirtualEarth)) {
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    VirtualEarth = GWorld->SpawnActor<AVirtualEarthActor>(Params);
    VirtualEarth->SetActorLabel("DynamicRadiusVirtualEarth");
    VirtualEarth->AddToRoot();
  }
  VirtualEarth->SetVirtualEarthRadii(Radius);
  return VirtualEarth;
}
