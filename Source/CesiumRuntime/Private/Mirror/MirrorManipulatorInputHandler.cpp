// Fill out your copyright notice in the Description page of Project Settings.

#include "Mirror/MirrorManipulatorInputHandler.h"
#include "Mirror/MirrorCoordinatesBPFuncLibrary.h"
#include "Mirror/MirrorEarthManipulatorBPLibrary.h"
void UMirrorManipulatorInputHandler::BeginPlay() {
  Super::BeginPlay();
  APawn* Owner = Cast<APawn>(GetOwner());
  MirrorMoveManagerComponent =
      Owner->GetComponentByClass<UMirrorMoveManagerComponent>();
}

FVector2D UMirrorManipulatorInputHandler::GetControllerMousePosition() {
  APawn* Owner = Cast<APawn>(GetOwner());
  APlayerController* Controller =
      Cast<APlayerController>(Owner->GetController());

  FVector2D MouseScreenPosition;
  Controller->GetMousePosition(MouseScreenPosition.X, MouseScreenPosition.Y);
  return MouseScreenPosition;
}

void UMirrorManipulatorInputHandler::PressedAction(FKey key) {
  FVector2D MouseScreenPosition = GetControllerMousePosition();
  if (key == EKeys::LeftMouseButton) {
    LeftMouseButtonPressed(MouseScreenPosition);
  }
}

void UMirrorManipulatorInputHandler::ReleasedAction(FKey key) {
  FVector2D MouseScreenPosition = GetControllerMousePosition();
  if (key == EKeys::LeftMouseButton) {
    LeftMouseButtonReleased(MouseScreenPosition);
  }
}

void UMirrorManipulatorInputHandler::LeftMouseButtonPressed(
    FVector2D MouseScreenPosition) {}

void UMirrorManipulatorInputHandler::LeftMouseButtonReleased(
    FVector2D MouseScreenPosition) {}

void UMirrorManipulatorInputHandler::MouseMoveAxis(float value) {
  FVector2D MouseScreenPosition = GetControllerMousePosition();
    OnMouseMove(MouseScreenPosition);
}

void UMirrorManipulatorInputHandler::OnMouseMove(
    const FVector2D& MouseScreenPosition) {}

UMirrorDragInputHandler::UMirrorDragInputHandler() {
}

void UMirrorDragInputHandler::BeginPlay() {
  Super::BeginPlay();
  VirtualEarthActor = GetWorld()->SpawnActor<AVirtualEarthActor>();
}

void UMirrorDragInputHandler::BeginDestroy() {
  Super::BeginDestroy();
  if (VirtualEarthActor && VirtualEarthActor->IsValidLowLevel()) {
    GetWorld()->DestroyActor(VirtualEarthActor);
  }
}

void UMirrorDragInputHandler::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  SinceLastDrag += DeltaTime;
}

void UMirrorDragInputHandler::LeftMouseButtonPressed(
    FVector2D MouseScreenPosition) {
  DraggingStartScreenPosition = MouseScreenPosition;
  IsLeftMouseButtonPressed = true;
  APawn* Owner = Cast<APawn>(GetOwner());
  APlayerController* Controller =
      Cast<APlayerController>(Owner->GetController());

  FVector UnrealLocation, UnrealDirection;
  Controller->DeprojectMousePositionToWorld(UnrealLocation, UnrealDirection);

  FHitResult HitResultInUnreal;

  if (UMirrorCoordinatesBPFuncLibrary::LineTraceRealEarthInUnreal(
          UnrealLocation,
          UnrealLocation + 99999999999 * UnrealDirection,
          HitResultInUnreal)) {
    IsDraggingAny = true;
  }


  FVector HitResultLocationInECEF =
      UMirrorCoordinatesBPFuncLibrary::UnrealToECEFLocation(
          HitResultInUnreal.Location);

  FTransform CameraInECEFTransform =
      UMirrorCoordinatesBPFuncLibrary::GetViewECEFTransform(Owner);

  DraggingStartEarthPositionInCameraCoordinate =
      CameraInECEFTransform.InverseTransformPosition(HitResultLocationInECEF);
  DraggingStartVirtualEarthRadius = HitResultLocationInECEF.Length();
}

void UMirrorDragInputHandler::LeftMouseButtonReleased(
    FVector2D MouseScreenPosition) {
  IsLeftMouseButtonPressed = false;
  IsDraggingAny = false;
}

void UMirrorDragInputHandler::OnMouseMove(
    const FVector2D& MouseScreenPosition) {
  if (!IsLeftMouseButtonPressed || SinceLastDrag < DraggingInterval ||
      !MirrorMoveManagerComponent || !MirrorMoveManagerComponent->IsValidLowLevelFast()) {
    return;
  }

  if (FVector2D::Distance(DraggingStartScreenPosition, MouseScreenPosition) <
      5) {
    return;
  }

  if (!IsDraggingAny) {
    return;
  }

  if (DraggingStartVirtualEarthRadius > (6378137.0 + 100000) ||
      DraggingStartVirtualEarthRadius < (6378137.0 - 100000)) {
    return;
  }

  DraggingStartScreenPosition = MouseScreenPosition;
  SinceLastDrag = 0;

  APawn* Owner = Cast<APawn>(GetOwner());
  APlayerController* Controller =
      Cast<APlayerController>(Owner->GetController());
  FVector UnrealLocation, UnrealDirection;
  Controller->DeprojectMousePositionToWorld(UnrealLocation, UnrealDirection);
  VirtualEarthActor->SetVirtualEarthRadii(
      FVector(DraggingStartVirtualEarthRadius));

  FVector ECEFLocation =
      UMirrorCoordinatesBPFuncLibrary::UnrealToECEFLocation(UnrealLocation);

  FVector ECEFDirection =
      UMirrorCoordinatesBPFuncLibrary::GetUnrealToECEFTransform()
          .TransformVector(UnrealDirection);

  FHitResult HitResultInECEF;
  if (!UMirrorCoordinatesBPFuncLibrary::LineTraceVirtualEarthInECEF(
          VirtualEarthActor,
          ECEFLocation,
          ECEFLocation + 9999999999999 * ECEFDirection,
          HitResultInECEF)) {
    return;
  }



  FTransform CameraInECEFTransform =
      UMirrorCoordinatesBPFuncLibrary::GetViewECEFTransform(Owner);

  DraggingNowEarthPositionInCameraCoordinate =
      CameraInECEFTransform.InverseTransformPosition(HitResultInECEF.Location);

  TArray<FTransform> MoveTransformInECEF =
      UMirrorEarthManipulatorBPLibrary::GetManipulatorMoveECEFTransform(
          CameraInECEFTransform,
          DraggingStartEarthPositionInCameraCoordinate,
          DraggingNowEarthPositionInCameraCoordinate,
          240);

  MirrorMoveManagerComponent->SetActorTransforms(
      EMirrorCoordinate::ECEF,
      MoveTransformInECEF,
      DraggingInterval);

  /* */
  DraggingStartEarthPositionInCameraCoordinate =
      DraggingNowEarthPositionInCameraCoordinate;
}

UMirrorScaleInputHandler::UMirrorScaleInputHandler() {}

void UMirrorScaleInputHandler::BeginPlay() { Super::BeginPlay(); }

void UMirrorScaleInputHandler::BeginDestroy() { Super::BeginDestroy(); }

void UMirrorScaleInputHandler::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction) {
   Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  SinceLastScale += DeltaTime;
}

void UMirrorScaleInputHandler::ScrollWheelAxis(float value) {
  if (FMath::IsNearlyEqual(value, 0) || SinceLastScale < ScalingInterval) {
    return;
  }
  SinceLastScale = 0;
  GEngine->AddOnScreenDebugMessage(
      -1,
      2,
      FColor::Cyan,
      FString::SanitizeFloat(value));
  double Scale;
  if (value > 0) {
    Scale = 1.0 /2.0;
  } else {
    Scale = 2.0 / 1.0;
    ;
  }

  FVector ScalePositionInCameraCoordinate;

  APawn* Owner = Cast<APawn>(GetOwner());
  APlayerController* Controller =
      Cast<APlayerController>(Owner->GetController());

  FVector2D CursorPosition;
  if (!Controller->GetMousePosition(CursorPosition.X, CursorPosition.Y)) {
    return;
  }

  FVector CursorECEFLocation, CursorECEFDirection;
  if (!UMirrorCoordinatesBPFuncLibrary::ScreenToECEF(
          Controller,
          CursorPosition,
          CursorECEFLocation,
          CursorECEFDirection)) {
    return;
  }

  FHitResult HitResultInECEF;

  if (!UMirrorCoordinatesBPFuncLibrary::LineTraceRealEarthInECEF(
          CursorECEFLocation,
          CursorECEFLocation + 9999999999999 * CursorECEFDirection,
          HitResultInECEF)) {
    return;
  }

  FTransform CameraInECEFTransform =
      UMirrorCoordinatesBPFuncLibrary::GetViewECEFTransform(Owner);


  TArray<FTransform> ScaleTransformInECEF =
      UMirrorEarthManipulatorBPLibrary::GetManipulatorScaleECEFTransform(
      CameraInECEFTransform,
      CameraInECEFTransform.InverseTransformPosition(HitResultInECEF.Location),
      CameraInECEFTransform.InverseTransformPosition(CursorECEFLocation),
      CameraInECEFTransform.InverseTransformVector(CursorECEFDirection),
      Scale,
      240);

    MirrorMoveManagerComponent->SetActorTransforms(
      EMirrorCoordinate::ECEF,
      ScaleTransformInECEF,
      ScalingInterval);
}

UMirrorRotateInputHandler::UMirrorRotateInputHandler() {}

void UMirrorRotateInputHandler::PressedAction(FKey key) {
    if (key == EKeys::MiddleMouseButton) {
    MouseMidButtonPressed();
    }
}

void UMirrorRotateInputHandler::ReleasedAction(FKey key) {
    if (key == EKeys::MiddleMouseButton) {
    MouseMidButtonReleased();
    }
}

void UMirrorRotateInputHandler::MouseMidButtonPressed() {
    APawn* Owner = Cast<APawn>(GetOwner());
    APlayerController* Controller =
        Cast<APlayerController>(Owner->GetController());

    bRotateClickDown = true;
    firstCursorScreenPosition = GetControllerMousePosition();
    lastCursorScreenPosition = GetControllerMousePosition();

    FVector CursorUnrealLocation, CursorUnrealDirection;
    Controller->DeprojectMousePositionToWorld(
        CursorUnrealLocation,
        CursorUnrealDirection);
    FVector CursorECEFLocation =
        UMirrorCoordinatesBPFuncLibrary::GetUnrealToECEFTransform()
            .TransformPosition(CursorUnrealLocation);

    FVector CursorECEFDirection =
        UMirrorCoordinatesBPFuncLibrary::GetUnrealToECEFTransform()
            .TransformVector(CursorUnrealDirection);

    FHitResult HitResultInECEF;   

    if (UMirrorCoordinatesBPFuncLibrary::LineTraceRealEarthInECEF(
            CursorECEFLocation,
            CursorECEFLocation + 999999999999999 * CursorECEFDirection,
            HitResultInECEF)) {
    bClickOnEarth = true;
    firstFocusPointInECEFCoordinate = HitResultInECEF.Location;
    } else {
    bClickOnEarth = false;
    }
}

void UMirrorRotateInputHandler::MouseMidButtonReleased() {
    bRotateClickDown = false;
}

void UMirrorRotateInputHandler::OnMouseMove(
    const FVector2D& MouseScreenPosition) {
    lastCursorScreenPosition = currentCursorScreenPosition;
    currentCursorScreenPosition = MouseScreenPosition;
    APawn* Owner = Cast<APawn>(GetOwner());

    if (bRotateClickDown && bClickOnEarth) {
    float xOffset =
        (currentCursorScreenPosition.X - lastCursorScreenPosition.X) / 6;
    float yOffset =
        (currentCursorScreenPosition.Y - lastCursorScreenPosition.Y) / 6;
    
    TArray<FTransform> RotateTransformInECEF =
        UMirrorEarthManipulatorBPLibrary::GetManipulatorRotateECEFTransform(
            UMirrorCoordinatesBPFuncLibrary::GetViewECEFTransform(Owner),
            firstFocusPointInECEFCoordinate,
            -xOffset,
            yOffset,
            1);
    MirrorMoveManagerComponent->SetActorTransforms(
        EMirrorCoordinate::ECEF,
        RotateTransformInECEF,
        0);
    }
    if (bRotateClickDown && !bClickOnEarth) {
    }

    FTransform CameraTransform =
        UMirrorCoordinatesBPFuncLibrary::GetViewECEFTransform(Owner);

    FTransform CameraInUnreal =
        UMirrorCoordinatesBPFuncLibrary::ECEFToUnrealTransform(CameraTransform);

        
}

UMirrorThrowInputHandler::UMirrorThrowInputHandler() {}

void UMirrorThrowInputHandler::BeginPlay() {
    Super::BeginPlay();
    VirtualEarthActor = GetWorld()->SpawnActor<AVirtualEarthActor>();
}

void UMirrorThrowInputHandler::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction) {
    AfterThrowClickStartTime += DeltaTime;
}

void UMirrorThrowInputHandler::LeftMouseButtonPressed(
    FVector2D MouseScreenPosition) {
    LeftMouseButtonPressedMousePosition = MouseScreenPosition;
    IsLeftMouseButtonPressed = true;
    APawn* Owner = Cast<APawn>(GetOwner());
    APlayerController* Controller =
        Cast<APlayerController>(Owner->GetController());

    FVector UnrealLocation, UnrealDirection;
    Controller->DeprojectMousePositionToWorld(UnrealLocation, UnrealDirection);

    FHitResult HitResultInUnreal;

    if (UMirrorCoordinatesBPFuncLibrary::LineTraceRealEarthInUnreal(
            UnrealLocation,
            UnrealLocation + 99999999999 * UnrealDirection,
            HitResultInUnreal)) {
    IsFirstCursorClickOnEarth = true;
    AfterThrowClickStartTime = 0;
    }

    FVector HitResultLocationInECEF =
        UMirrorCoordinatesBPFuncLibrary::UnrealToECEFLocation(
            HitResultInUnreal.Location);

    FTransform CameraInECEFTransform =
        UMirrorCoordinatesBPFuncLibrary::GetViewECEFTransform(Owner);

    ThrowStartEarthPositionInCameraCoordinate =
        CameraInECEFTransform.InverseTransformPosition(HitResultLocationInECEF);
    ThrowStartVirtualEarthRadius = HitResultLocationInECEF.Length();
}

void UMirrorThrowInputHandler::LeftMouseButtonReleased(
    FVector2D MouseScreenPosition) {
    LeftMouseButtonReleasedMousePosition = MouseScreenPosition;
    if (!IsFirstCursorClickOnEarth) {
    return;
    }

    if (AfterThrowClickStartTime > ThrowInterval) {
    return;
    }
    IsFirstCursorClickOnEarth = false;

    APawn* Owner = Cast<APawn>(GetOwner());
    APlayerController* Controller =
        Cast<APlayerController>(Owner->GetController());
    FVector UnrealLocation, UnrealDirection;
    Controller->DeprojectMousePositionToWorld(UnrealLocation, UnrealDirection);
    VirtualEarthActor->SetVirtualEarthRadii(
        FVector(ThrowStartVirtualEarthRadius));

    FVector ECEFLocation =
        UMirrorCoordinatesBPFuncLibrary::UnrealToECEFLocation(UnrealLocation);

    FVector ECEFDirection =
        UMirrorCoordinatesBPFuncLibrary::GetUnrealToECEFTransform()
            .TransformVector(UnrealDirection);

    FHitResult HitResultInECEF;
    if (!UMirrorCoordinatesBPFuncLibrary::LineTraceVirtualEarthInECEF(
            VirtualEarthActor,
            ECEFLocation,
            ECEFLocation + 9999999999999 * ECEFDirection,
            HitResultInECEF)) {
    return;
    }

    FTransform CameraInECEFTransform =
        UMirrorCoordinatesBPFuncLibrary::GetViewECEFTransform(Owner);

    FVector ThrowNowEarthPositionInCameraCoordinate =
        CameraInECEFTransform.InverseTransformPosition(
            HitResultInECEF.Location);
 
  TArray<FTransform> ThrowTransformInECEF =
        UMirrorEarthManipulatorBPLibrary::GetManipulatorThrowECEFTransform(
            CameraInECEFTransform,
            ThrowStartEarthPositionInCameraCoordinate,
            ThrowNowEarthPositionInCameraCoordinate,
            240,
            ThrowTime);

    MirrorMoveManagerComponent->SetActorTransforms(
        EMirrorCoordinate::ECEF,
      ThrowTransformInECEF,
        ThrowTime);
}
