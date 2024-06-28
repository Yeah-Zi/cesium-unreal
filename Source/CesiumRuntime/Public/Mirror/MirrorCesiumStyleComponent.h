// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Optional.h"
#include "Templates/Tuple.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "ScriptX/src/include/ScriptX/ScriptX.h"
#include <v8.h>
#include "MirrorCesiumStyleComponent.generated.h"
struct Style {
  TOptional<FColor> Color;
  TOptional<bool> Show;
};

struct Expression {
  TOptional<TArray<TTuple<FString, FString>>> Defines;
  TOptional<TArray<TTuple<FString, FString>>> Color;
  TOptional<TArray<TTuple<FString, FString>>> Show;

  Expression(FString JsonString) {
    TSharedRef<TJsonReader<TCHAR>> Reader =
        TJsonReaderFactory<TCHAR>::Create(JsonString);
    TSharedPtr<FJsonObject> JsonObject;
    if (!FJsonSerializer::Deserialize(Reader, JsonObject) ||
        !JsonObject.IsValid()) {
      return;
    }

    {
      // 从JSON对象中提取数据
      TSharedPtr<FJsonObject> DefinesJsonObject =
          JsonObject->GetObjectField("defines");

      TArray<TTuple<FString, FString>> TempDefines;
      for (auto define : DefinesJsonObject->Values) {
        TTuple<FString, FString> tuple(define.Key, define.Value->AsString());
        TempDefines.Add(tuple);
      }

      Defines = TempDefines;
    }

    {
      if (JsonObject->HasField("color")) {
        TArray<TSharedPtr<FJsonValue>> ColorConditionsJsonObject =
            JsonObject->GetObjectField("color")->GetArrayField("conditions");
        for (size_t i = 0; i < ColorConditionsJsonObject.Num(); i++) {
          TArray<TSharedPtr<FJsonValue>> condition =
              ColorConditionsJsonObject[i]->AsArray();
          if (condition.Num() != 2) {
            continue;
          }

          TTuple<FString, FString> tuple(
              condition[0]->AsString(),
              condition[1]->AsString());
          Color->Add(tuple);
        }
      }
    }

    {
      if (JsonObject->HasField("show")) {
        TArray<TSharedPtr<FJsonValue>> ShowConditionsJsonObject =
            JsonObject->GetObjectField("show")->GetArrayField("conditions");
        for (size_t i = 0; i < ShowConditionsJsonObject.Num(); i++) {
          TArray<TSharedPtr<FJsonValue>> condition =
              ShowConditionsJsonObject[i]->AsArray();
          if (condition.Num() != 2) {
            continue;
          }

          TTuple<FString, FString> tuple(
              condition[0]->AsString(),
              condition[1]->AsString());
          Show->Add(tuple);
        }
      }
    }
  }
};
using namespace script;

UCLASS(ClassGroup=(Custom))
class CESIUMRUNTIME_API UMirrorCesiumStyleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMirrorCesiumStyleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  std::shared_ptr<script::ScriptEngine> V8Engine;

  TWeakObjectPtr<USceneComponent> Target;

  int64 FeatureIDSetIndex = 0;

  //TArray<Style>
  //Evaluate(const Expression& expression, const int64& FeatureIDSetIndex);

  bool SetEvaluateFeatureIDSetIndex(const int64& inFeatureIDSetIndex);

  bool Evaluate(const Expression& expression);

  TArray<FString> GetFeatureIDSetMetadata();
};
