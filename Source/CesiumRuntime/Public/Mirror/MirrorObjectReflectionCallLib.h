// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MirrorObjectReflectionCallLib.generated.h"

class FProperty;
class FByteProperty;
class FUInt16Property;
class FUInt32Property;
class FUInt64Property;
class FInt8Property;
class FInt16Property;
class FIntProperty;
class FInt64Property;
class FBoolProperty;
class FFloatProperty;
class FDoubleProperty;
class FObjectPropertyBase;
class FObjectProperty;
class FClassProperty;
class FInterfaceProperty;
class FWeakObjectProperty;
class FLazyObjectProperty;
class FSoftObjectProperty;
class FSoftClassProperty;
class FNameProperty;
class FStructProperty;
class FStrProperty;
class FTextProperty;
class FArrayProperty;
class FDelegateProperty;
class FMulticastDelegateProperty;
class FMapProperty;
class FSetProperty;
class FEnumProperty;

template <class T, class V>
bool SetObjectProperty(UObject* Object, FName Property, V Value) {
  static_assert(
      std::is_base_of<FProperty, T>::value,
      "T must be a subclass of Base");

  T* Prop = FindFProperty<T>(
      Object->GetClass(),
      Property); // try to find float property in Target named VarName
  if (!Prop)     // if we found variable
  {
    return false;
  }
  Prop->SetPropertyValue_InContainer(
      Object,
      Value); // this actually sets the variable
  return true;
}

template <class T, class V>
bool GetObjectProperty(UObject* Object, FName Property, V& Value) {
  static_assert(
      std::is_base_of<FProperty, T>::value,
      "T must be a subclass of Base");

  T* Prop = FindFProperty<T>(
      Object->GetClass(),
      Property); // try to find float property in Target named VarName
  if (!Prop)     // if we found variable
  {
    return false;
  }
  Value = Prop->GetPropertyValue(Object);
  return true;
}

UCLASS()
class CESIUMRUNTIME_API UMirrorObjectReflectionCallLib
    : public UBlueprintFunctionLibrary {
  GENERATED_BODY()
public:
  static bool
  SetObjectFByteProperty(UObject* Object, FName Property, uint8 Value);

  static bool
  SetObjectFUInt16Property(UObject* Object, FName Property, uint16 Value);

  static bool
  SetObjectFUInt32Property(UObject* Object, FName Property, uint32 Value);

  static bool
  SetObjectFUInt64Property(UObject* Object, FName Property, int64 Value);

  static bool
  SetObjectFInt8Property(UObject* Object, FName Property, int8 Value);

  static bool
  SetObjectFInt16Property(UObject* Object, FName Property, int16 Value);

  static bool SetObjectFIntProperty(UObject* Object, FName Property, int Value);

  static bool
  SetObjectFInt64Property(UObject* Object, FName Property, int64 Value);

  static bool
  SetObjectFBoolProperty(UObject* Object, FName Property, bool Value);

  static bool
  SetObjectFFloatProperty(UObject* Object, FName Property, float Value);

  static bool
  SetObjectFDoubleProperty(UObject* Object, FName Property, double Value);

  // UFUNCTION(BlueprintCallable, Category = "SetObjectFProperty")
  // bool SetObjectFObjectPropertyBase(UObject* Object, FName Property,
  // UObjectBaseUtility* Value);

  static bool
  SetObjectFObjectProperty(UObject* Object, FName Property, UObject* Value);

  static bool
  SetObjectFClassProperty(UObject* Object, FName Property, UClass* Value);

  static bool SetObjectFInterfaceProperty(
      UObject* Object,
      FName Property,
      UInterface* Value);

  // UFUNCTION(BlueprintCallable, Category = "SetObjectFProperty")
  // bool SetObjectFWeakObjectProperty(UObject* Object, FName Property,
  // TWeakObjectPtr<UObject> Value);

  // UFUNCTION(BlueprintCallable, Category = "SetObjectFProperty")
  // bool SetObjectFLazyObjectProperty(UObject* Object, FName Property, uint8
  // Value);

  // UFUNCTION(BlueprintCallable, Category = "SetObjectFProperty")
  // bool SetObjectFSoftObjectProperty(UObject* Object, FName Property, uint8
  // Value);

  // UFUNCTION(BlueprintCallable, Category = "SetObjectFProperty")
  // bool SetObjectFSoftClassProperty(UObject* Object, FName Property,
  // UInterface* Value);
  static bool
  SetObjectFNameProperty(UObject* Object, FName Property, FName Value);

  // UFUNCTION(BlueprintCallable, Category = "SetObjectFProperty")
  // bool SetObjectFStructProperty(UObject* Object, FName Property, void*
  // Value);

  static bool
  SetObjectFStrProperty(UObject* Object, FName Property, FString Value);

  static bool
  SetObjectFTextProperty(UObject* Object, FName Property, FText Value);

  // UFUNCTION(BlueprintCallable, Category = "SetObjectFProperty")
  // bool SetObjectFArrayProperty(UObject* Object, FName Property, TArray<void*>
  // Value);

  // UFUNCTION(BlueprintCallable, Category = "SetObjectFProperty")
  // bool SetObjectFDelegateProperty(UObject* Object, FName Property, void*
  // Value);

  // UFUNCTION(BlueprintCallable, Category = "SetObjectFProperty")
  // bool SetObjectFMulticastDelegateProperty(UObject* Object, FName Property,
  // void* Value);

  // UFUNCTION(BlueprintCallable, Category = "SetObjectFProperty")
  // bool SetObjectFMapProperty(UObject* Object, FName Property, void* Value);

  // UFUNCTION(BlueprintCallable, Category = "SetObjectFProperty")
  // bool SetObjectFSetProperty(UObject* Object, FName Property, void* Value);

  static bool
  SetObjectFEnumProperty(UObject* Object, FName Property, uint8 Value);
};
