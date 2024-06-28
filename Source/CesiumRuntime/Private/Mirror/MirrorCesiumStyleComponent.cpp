// Fill out your copyright notice in the Description page of Project Settings.

#include "Mirror/MirrorCesiumStyleComponent.h"
#include "CesiumGltfPrimitiveComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CesiumMaterialUserData.h"
#include "CesiumMetadataUtilityBlueprintLibrary.h"
#include "CesiumPropertyTable.h"
#include "CesiumMetadataValue.h"
#include "Interfaces/IPluginManager.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const char* javascriptCode = R"(
function ComputeExpressionResult(expression, metadatas)
{
  const ast = jsep(expression);
	const result =  new Array();

  for (const value of modelMetadata) {
    result.push(executor.evaluate(ast));
  }
  return result;
}
)";


// Sets default values for this component's properties
UMirrorCesiumStyleComponent::UMirrorCesiumStyleComponent() {
  // Set this component to be initialized when the game starts, and to be ticked
  // every frame.  You can turn these features off to improve performance if you
  // don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...
}

// Called when the game starts
void UMirrorCesiumStyleComponent::BeginPlay() {
  Super::BeginPlay();
  FString ContentDir = IPluginManager::Get()
                           .FindPlugin(TEXT("CesiumForUnreal"))
                           ->GetContentDir() +
                       "/";
  const TCHAR* CharArray = *ContentDir;
  char* CharArrayAsAnsi = TCHAR_TO_ANSI(CharArray);

  v8::V8::InitializeICUDefaultLocation(CharArrayAsAnsi);
  v8::V8::InitializeExternalStartupData(CharArrayAsAnsi);
  V8Engine =
      std::shared_ptr<script::ScriptEngine>{
          new script::ScriptEngineImpl(),
          script::ScriptEngine::Deleter()};
  script::EngineScope enter(V8Engine.get());
  FString str;
  FFileHelper::LoadFileToString(str, *(ContentDir + "jsep.js"));
  try {
    V8Engine->eval(TCHAR_TO_UTF8(*str));
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

// Called every frame
void UMirrorCesiumStyleComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UMirrorCesiumStyleComponent::SetEvaluateFeatureIDSetIndex(
    const int64& inFeatureIDSetIndex) {
  if (!IsValid(Target.Get())) {
    return false;
  }
  UCesiumGltfPrimitiveComponent* GltfPrimitiveComponent =
      Cast<UCesiumGltfPrimitiveComponent>(Target.Get());
  if (!GltfPrimitiveComponent) {
    return false;
  }

  if (!GltfPrimitiveComponent->GetStaticMesh()) {
    return false;
  }

  const FCesiumPrimitiveFeatures& features = GltfPrimitiveComponent->Features;
  const TArray<FCesiumFeatureIdSet>& featureIDSets =
      UCesiumPrimitiveFeaturesBlueprintLibrary::GetFeatureIDSets(features);
  if (FeatureIDSetIndex < 0 || FeatureIDSetIndex >= featureIDSets.Num()) {
    return false;
  }

  FeatureIDSetIndex = inFeatureIDSetIndex;

  auto Indices = GltfPrimitiveComponent->GetStaticMesh()
                     ->GetRenderData()
                     ->LODResources[0]
                     .IndexBuffer.GetArrayView();

  FStaticMeshRenderData* RenderData =
    GltfPrimitiveComponent->GetStaticMesh()->GetRenderData();

  static const uint8 TargetVertexUVChannel = 7;

  for (size_t j = 0; j < Indices.Num(); j++) {
    int64 featureID =
        UCesiumFeatureIdSetBlueprintLibrary::GetFeatureIDForVertex(
            featureIDSets[FeatureIDSetIndex],
            Indices[j]);

    FVector2f UV;
    UV.X = featureID;

    RenderData->LODResources[0]
    .VertexBuffers.StaticMeshVertexBuffer.SetVertexUV(
        Indices[j], TargetVertexUVChannel, UV);
  }

  return true;
}
std::string readFileToString(const std::string& filePath) {
  std::ifstream file(filePath, std::ios::in | std::ios::binary);
  if (!file) {
    throw std::runtime_error("Failed to open file: " + filePath);
  }

  std::ostringstream contents;
  contents << file.rdbuf();
  file.close();

  return contents.str();
}
bool UMirrorCesiumStyleComponent::Evaluate(const Expression& expression) {

  TArray<FString> featureMetadata = GetFeatureIDSetMetadata();
  script::EngineScope enter(V8Engine.get());
  std::string js_code =
      readFileToString("D:/GitHubProject/新建文件夹/src/jsep.js");
  script::EngineScope enter(V8Engine.get());



  return false;
}


auto ConvertTMapToJson = [](const TMap<FString, FString>& StringMap) {
  FString JsonString = TEXT("{");

  // 遍历 TMap 并将键值对拼接到 JsonString
  for (const auto& Entry : StringMap) {
    // 将键和值转义处理
    FString EscapedKey = Entry.Key;
    FString EscapedValue = Entry.Value;

    EscapedKey =
        EscapedKey.Replace(TEXT("\n"), TEXT(" "), ESearchCase::CaseSensitive);
    EscapedValue =
        EscapedValue.Replace(TEXT("\n"), TEXT(" "), ESearchCase::CaseSensitive);

    EscapedKey =
        EscapedKey.Replace(TEXT("\""), TEXT("\'"), ESearchCase::CaseSensitive);
    EscapedValue = EscapedValue.Replace(
        TEXT("\""),
        TEXT("\'"),
        ESearchCase::CaseSensitive);

    JsonString = JsonString + "\"" + EscapedKey + "\"" + ":" + "\"" +
                 EscapedValue + "\"" + ",";
  }

  // 移除末尾多余的逗号
  if (StringMap.Num() > 0) {
    JsonString.RemoveAt(JsonString.Len() - 1);
  }

  JsonString += TEXT("}");

  return JsonString;
};

TArray<FString> UMirrorCesiumStyleComponent::GetFeatureIDSetMetadata() {
  UCesiumGltfPrimitiveComponent* GltfPrimitiveComponent =
      Cast<UCesiumGltfPrimitiveComponent>(Target);
  if (!GltfPrimitiveComponent ||
      !GltfPrimitiveComponent->IsValidLowLevelFast() ||
      GltfPrimitiveComponent->IsBeingDestroyed()) {
    return TArray<FString>();
  }

  if (!GltfPrimitiveComponent->GetStaticMesh()) {
    return TArray<FString>();
  }

  const FCesiumPrimitiveFeatures& features = GltfPrimitiveComponent->Features;
  const TArray<FCesiumFeatureIdSet>& featureIDSets =
      UCesiumPrimitiveFeaturesBlueprintLibrary::GetFeatureIDSets(features);
  if (FeatureIDSetIndex < 0 || FeatureIDSetIndex >= featureIDSets.Num()) {
    return TArray<FString>();
  }
  const FCesiumFeatureIdSet& featureIDSet = featureIDSets[FeatureIDSetIndex];
  const int64 propertyTableIndex =
      UCesiumFeatureIdSetBlueprintLibrary::GetPropertyTableIndex(featureIDSet);
  auto count =
      UCesiumFeatureIdSetBlueprintLibrary::GetFeatureCount(featureIDSet);
  if (count <= 0) {
    return TArray<FString>();
  }
  FCesiumModelMetadata Metadata;
  Metadata = UCesiumModelMetadataBlueprintLibrary::GetModelMetadata(
      GltfPrimitiveComponent);
  const TArray<FCesiumPropertyTable>& propertyTables =
      UCesiumModelMetadataBlueprintLibrary::GetPropertyTables(Metadata);
  if (propertyTableIndex < 0 || propertyTableIndex >= propertyTables.Num()) {
    return TArray<FString>();
  }
  const FCesiumPropertyTable& propertyTable =
      propertyTables[propertyTableIndex];

  int64 FeatureCount = UCesiumFeatureIdSetBlueprintLibrary::GetFeatureCount(
      featureIDSets[FeatureIDSetIndex]);

  TArray<FString> FeatureIDAndMetaDataJsonArray;
  FeatureIDAndMetaDataJsonArray.Init(FString(), FeatureCount);
  auto Indices = GltfPrimitiveComponent->GetStaticMesh()
                     ->GetRenderData()
                     ->LODResources[0]
                     .IndexBuffer.GetArrayView();


  TArray<FString> Results;



  for (size_t i = 0; i < Indices.Num(); i++) {
    int64 featureID =
        UCesiumFeatureIdSetBlueprintLibrary::GetFeatureIDForVertex(
            featureIDSets[FeatureIDSetIndex],
            Indices[i]);
    if (featureID < 0) {
      continue;
    }
    if (!FeatureIDAndMetaDataJsonArray[featureID].IsEmpty()) {
      continue;
    }

    TMap<FString, FString> featureMetadata = UCesiumPropertyTableBlueprintLibrary::GetMetadataValuesForFeatureAsStrings(
        propertyTable,
        featureID);
    Results.Add(ConvertTMapToJson(featureMetadata));

    TMap<FString, FCesiumPropertyTableProperty> properties =
        UCesiumPropertyTableBlueprintLibrary::GetProperties(propertyTable);
    for (auto pair : properties) {
          UCesiumPropertyTablePropertyBlueprintLibrary::GetBlueprintType(
          pair.Value);
    }

    //auto result =
    //    UCesiumPropertyTableBlueprintLibrary::GetMetadataValuesForFeature(
    //        propertyTable,
    //        featureID);

    //auto dataStrings =
    //    UCesiumMetadataValueBlueprintLibrary::GetValuesAsStrings(result);

  }

  return Results;
}

