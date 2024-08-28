// Fill out your copyright notice in the Description page of Project Settings.


#include "Mirror/MirrorObjectReflectionCallLib.h"

bool UMirrorObjectReflectionCallLib::SetObjectFByteProperty(
    UObject* Object,
    FName Property,
    uint8 Value) {
  return SetObjectProperty<FByteProperty>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFUInt16Property(
    UObject* Object,
    FName Property,
    uint16 Value) {
  return SetObjectProperty<FUInt16Property>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFUInt32Property(
    UObject* Object,
    FName Property,
    uint32 Value) {
  return SetObjectProperty<FUInt32Property>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFUInt64Property(
    UObject* Object,
    FName Property,
    int64 Value) {
  return SetObjectProperty<FUInt64Property>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFInt8Property(
    UObject* Object,
    FName Property,
    int8 Value) {
  return SetObjectProperty<FInt8Property>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFInt16Property(
    UObject* Object,
    FName Property,
    int16 Value) {
  return SetObjectProperty<FInt16Property>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFIntProperty(
    UObject* Object,
    FName Property,
    int Value) {
  return SetObjectProperty<FIntProperty>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFInt64Property(
    UObject* Object,
    FName Property,
    int64 Value) {
  return SetObjectProperty<FInt64Property>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFBoolProperty(
    UObject* Object,
    FName Property,
    bool Value) {
  return SetObjectProperty<FBoolProperty>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFFloatProperty(
    UObject* Object,
    FName Property,
    float Value) {
  return SetObjectProperty<FFloatProperty>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFDoubleProperty(
    UObject* Object,
    FName Property,
    double Value) {
  return SetObjectProperty<FDoubleProperty>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFObjectProperty(
    UObject* Object,
    FName Property,
    UObject* Value) {
  return SetObjectProperty<FObjectProperty>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFClassProperty(
    UObject* Object,
    FName Property,
    UClass* Value) {
  return SetObjectProperty<FClassProperty>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFInterfaceProperty(
    UObject* Object,
    FName Property,
    UInterface* Value) {
  return false;
}

bool UMirrorObjectReflectionCallLib::SetObjectFNameProperty(
    UObject* Object,
    FName Property,
    FName Value) {
  return SetObjectProperty<FNameProperty>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFStructProperty(
    UObject* Object,
    FName Property,
    void* Value) {
  FProperty* Prop = Object->GetClass()->FindPropertyByName(Property);
  if (!Prop) // if we found variable
  {
    return false;
  }
  Prop->SetValue_InContainer(Object, Value);
  return true;

  //return SetObjectProperty<FStructProperty>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFStrProperty(
    UObject* Object,
    FName Property,
    FString Value) {
  return SetObjectProperty<FStrProperty>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFTextProperty(
    UObject* Object,
    FName Property,
    FText Value) {
  return SetObjectProperty<FTextProperty>(Object, Property, Value);
}

bool UMirrorObjectReflectionCallLib::SetObjectFEnumProperty(
    UObject* Object,
    FName Property,
    uint8 Value) {
  FProperty* Prop = Object->GetClass()->FindPropertyByName(Property);
  if (!Prop) // if we found variable
  {
    return false;
  }
  Prop->SetValue_InContainer(Object, &Value);
  return false;
}
