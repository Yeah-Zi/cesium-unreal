// Fill out your copyright notice in the Description page of Project Settings.

#include "Mirror/MirrorInputRegisterComponent.h"

// Sets default values for this component's properties
UMirrorInputRegisterComponent::UMirrorInputRegisterComponent() {
  // Set this component to be initialized when the game starts, and to be ticked
  // every frame.  You can turn these features off to improve performance if you
  // don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...
}

// Called when the game starts
void UMirrorInputRegisterComponent::BeginPlay() {
  Super::BeginPlay();
  Ownner = Cast<AActor>(this->GetOwner());
  if (Ownner) {
    RegisterInput(Ownner->InputComponent);
  }
}

// Called every frame
void UMirrorInputRegisterComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // ...
}

void UMirrorInputRegisterComponent::RegisterInput(
    UInputComponent* InInputComponent) {
  InputComponent = InInputComponent;
  if (!InputComponent) {
    return;
  }
  TArray<FKey> ActionKeys = {
      EKeys::One,
      EKeys::Two,
      EKeys::Three,
      EKeys::Four,
      EKeys::Five,
      EKeys::Six,
      EKeys::Seven,
      EKeys::Eight,
      EKeys::Nine,
      EKeys::Zero,
      EKeys::Hyphen,
      EKeys::Equals,
      EKeys::Tab,
      EKeys::A,
      EKeys::B,
      EKeys::C,
      EKeys::D,
      EKeys::E,
      EKeys::F,
      EKeys::G,
      EKeys::H,
      EKeys::I,
      EKeys::J,
      EKeys::K,
      EKeys::L,
      EKeys::M,
      EKeys::N,
      EKeys::O,
      EKeys::P,
      EKeys::Q,
      EKeys::R,
      EKeys::S,
      EKeys::T,
      EKeys::U,
      EKeys::V,
      EKeys::W,
      EKeys::X,
      EKeys::Y,
      EKeys::Z,
      EKeys::SpaceBar,
      EKeys::Enter,
      EKeys::LeftShift,
      EKeys::LeftControl,
      EKeys::LeftAlt,
      EKeys::LeftMouseButton,
      EKeys::MiddleMouseButton,
      EKeys::RightMouseButton,
  };
  for (FKey key : ActionKeys) {

    FName keyUniqueName(
        key.GetFName().ToString() + "_" + FGuid::NewGuid().ToString());

    UPlayerInput::AddEngineDefinedActionMapping(
        FInputActionKeyMapping(keyUniqueName, key));

    allActionBinding.Add(&InputComponent->BindAction(
        keyUniqueName,
        IE_Released,
        this,
        &UMirrorInputRegisterComponent::ReleasedAction));

    allActionBinding.Add(&InputComponent->BindAction(
        keyUniqueName,
        IE_Pressed,
        this,
        &UMirrorInputRegisterComponent::PressedAction));
  }

  {
    FName scrollWheelUniqueName("ScrollWheelAxis_" + FGuid::NewGuid().ToString());
    FName mouseMoveUniqueName("MouseMoveAxis_" + FGuid::NewGuid().ToString());
    UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping(
        scrollWheelUniqueName,
        EKeys::MouseWheelAxis,
        1.0f));
    allAxisBinding.Add(&InputComponent->BindAxis(
        scrollWheelUniqueName,
        this,
        &UMirrorInputRegisterComponent::ScrollWheelAxis));

    UPlayerInput::AddEngineDefinedAxisMapping(
        FInputAxisKeyMapping(mouseMoveUniqueName));
    allAxisBinding.Add(&InputComponent->BindAxis(
        mouseMoveUniqueName,
        this,
        &UMirrorInputRegisterComponent::MouseMoveAxis));
  }

}

void UMirrorInputRegisterComponent::UnregisterInput() {
  for (auto action : allActionBinding) {
    InputComponent->RemoveActionBinding(
        action->GetActionName(),
        action->KeyEvent);
  }

  for (auto axis : allAxisBinding) {

    InputComponent->RemoveAxisBinding(axis->AxisName);
  }
  allActionBinding.Empty();
  allAxisBinding.Empty();
}

void UMirrorInputRegisterComponent::ScrollWheelAxis(float value) {}

void UMirrorInputRegisterComponent::MouseMoveAxis(float value) {}

void UMirrorInputRegisterComponent::PressedAction(FKey key) {}

void UMirrorInputRegisterComponent::ReleasedAction(FKey key) {}
