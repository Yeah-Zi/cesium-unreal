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
#include "../CesiumMetadataValue.h"
#include "MirrorCesiumStyleComponent.generated.h"
struct Style {
  TOptional<FColor> Color;
  TOptional<bool> Show;
};

struct Expression {
  std::optional<std::vector<std::tuple<FString, FString>>> Defines;
  std::optional<std::variant<std::string, std::vector<std::tuple<FString, FString>>>> Color;
  std::optional<std::variant<std::string, std::vector<std::tuple<FString, FString>>>> Show;

  Expression(FString JsonString) {
    return;
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

      std::vector<std::tuple<FString, FString>> TempDefines;
      for (auto define : DefinesJsonObject->Values) {
        std::tuple<FString, FString> tuple(
            define.Key,
            define.Value->AsString());
        TempDefines.push_back(tuple);
      }

      Defines = TempDefines;
    }

    {
      std::vector<std::tuple<FString, FString>> ColorExpression;
      if (JsonObject->HasField("color")) {
        if (JsonObject->GetObjectField("color")->HasField("conditions")) {
          TArray<TSharedPtr<FJsonValue>> ColorConditionsJsonObject =
              JsonObject->GetObjectField("color")->GetArrayField("conditions");
          for (size_t i = 0; i < ColorConditionsJsonObject.Num(); i++) {
            TArray<TSharedPtr<FJsonValue>> condition =
                ColorConditionsJsonObject[i]->AsArray();
            if (condition.Num() != 2) {
              continue;
            }

            std::tuple<FString, FString> tuple(
                condition[0]->AsString(),
                condition[1]->AsString());
            ColorExpression.push_back(tuple);
          }
        }
        Color = ColorExpression;
      } else {
        Color = TCHAR_TO_UTF8(*JsonObject->GetStringField("color"));
      }
    }

    {
      std::vector<std::tuple<FString, FString>> ShowExpression;

      if (JsonObject->HasField("show")) {
        if (JsonObject->GetObjectField("show")->HasField("conditions")) {
          TArray<TSharedPtr<FJsonValue>> ShowConditionsJsonObject =
              JsonObject->GetObjectField("show")->GetArrayField("conditions");
          for (size_t i = 0; i < ShowConditionsJsonObject.Num(); i++) {
            TArray<TSharedPtr<FJsonValue>> condition =
                ShowConditionsJsonObject[i]->AsArray();
            if (condition.Num() != 2) {
              continue;
            }

            std::tuple<FString, FString> tuple(
                condition[0]->AsString(),
                condition[1]->AsString());
            ShowExpression.push_back(tuple);
          }
          Show = ShowExpression;
        } else {
          Show = TCHAR_TO_UTF8(*JsonObject->GetStringField("show"));
        }
      }
    }
  }
};

UCLASS()
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

  bool Evaluate(const FString& expression);

  TArray<bool> ComputeExpressionBoolResult(
      const FString& Expression,
      const script::Local<script::Value>& arg);

  TArray<FColor> ComputeExpressionColorResult(
      const FString& Expression,
      const script::Local<script::Value>& arg);

  static script::Local<script::Value>
  CesiumMetadataToLocalValue(const FCesiumMetadataValue& Metadata);
  TArray<FString> GetFeatureIDSetMetadata();

  std::vector<script::Local<script::Value>>
  GetFeatureIDSetMetadataScriptValue();
};
