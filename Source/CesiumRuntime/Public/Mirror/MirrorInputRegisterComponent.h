// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "InputCoreTypes.h"
#include "MirrorInputRegisterComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CESIUMRUNTIME_API UMirrorInputRegisterComponent : public UActorComponent {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UMirrorInputRegisterComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

  UPROPERTY(VisibleAnywhere)
  UInputComponent* InputComponent;

  UPROPERTY(VisibleAnywhere)
  AActor* Ownner = nullptr;

  TArray<FInputAxisBinding*> allAxisBinding;

  TArray<FInputActionBinding*> allActionBinding;

public:
  // Called every frame
  virtual void TickComponent(
      float DeltaTime,
      ELevelTick TickType,
      FActorComponentTickFunction* ThisTickFunction) override;

  virtual void RegisterInput(UInputComponent* InInputComponent);

  virtual void UnregisterInput();

public:
  virtual void ScrollWheelAxis(float value);

  virtual void MouseMoveAxis(float value);

  virtual void PressedAction(struct FKey key);

  virtual void ReleasedAction(struct FKey key);

};
