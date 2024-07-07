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
#include "CesiumRuntime/Public/CesiumPropertyArrayBlueprintLibrary.h"
#include "Engine/Texture2D.h"
#include "HAL/PlatformProcess.h"
#include "Async/Async.h"

const char* javascriptCode = R"(
function ComputeExpressionResult(ast, metadata)
{
  return executor.evaluateWithVariables(ast, metadata); 
}

function RunExpressionConditions(conditions, metadatas)
{
    var Result = [];
  { // Expression
    bool singleCondition = true;
    var ast;
    if (typeof conditions == "string")
    {
      colorAst = jsep(conditions);
    }
    else
    {
      singleCondition = false;
      ast = [];
      for(const condition : conditions.conditions)
      {
        ast.push({"conditionAst": jsep(condition[0]), "resultAst": jsep(condition[1])});
      }
    }
    if(singleCondition)
    {
      for (var metadata of metadatas) {
        Result.push(ComputeExpressionResult(ast, metadata));
      }      
    }
    else
    {
      for (var metadata of metadatas) {
        for(var condition : ast)
        {
          if(ComputeExpressionResult(condition["conditionAst"]))
          {
            Result.push(ComputeExpressionResult(condition["resultAst"], metadata));
            break;
          }
        }
      }    
    }
  }
  return Result;
}

function Styling(expressionStr, metadatas)
{
  const expressionObj = JSON.parse(expressionStr);
  var colorResult = RunExpressionConditions(expressionObj.color, metadatas);
  var showResult = RunExpressionConditions(expressionObj.show, metadatas);

  return {"color":colorResult, "show":showResult};
}
)";

using namespace script;
// Sets default values for this component's properties
UMirrorCesiumStyleComponent::UMirrorCesiumStyleComponent(){
  // Set this component to be initialized when the game starts, and to be ticked
  // every frame.  You can turn these features off to improve performance if you
  // don't need them.
  PrimaryComponentTick.bCanEverTick = true;
  FString ContentDir = IPluginManager::Get()
                           .FindPlugin(TEXT("CesiumForUnreal"))
                           ->GetContentDir() +
                       "/JavaScript/";
  const TCHAR* CharArray = *ContentDir;
  char* CharArrayAsAnsi = TCHAR_TO_ANSI(CharArray);

  v8::V8::InitializeICUDefaultLocation(CharArrayAsAnsi);
  v8::V8::InitializeExternalStartupData(CharArrayAsAnsi);
  V8Engine = std::shared_ptr<script::ScriptEngine>{
      new script::ScriptEngineImpl(),
      script::ScriptEngine::Deleter()};
  script::EngineScope enter(V8Engine.get());

  try {
    auto log = Function::newFunction([](const std::string& msg) {
      UE_LOG(LogTemp, Warning, TEXT("[log]: %s"), msg.c_str());
      //std::cout << "[log]: " << msg << std::endl;
    });
    V8Engine->set("log", log);
    {
      FString str;
      FFileHelper::LoadFileToString(str, *(ContentDir + "Color.js"));
      // V8Engine->eval("log('hello world');");
      V8Engine->eval(TCHAR_TO_UTF8(*str));
    }
    {
      FString str;
      FFileHelper::LoadFileToString(str, *(ContentDir + "jsep.js"));
      // V8Engine->eval("log('hello world');");
      V8Engine->eval(TCHAR_TO_UTF8(*str));
    }


  } catch (const script::Exception& e) {
    std::cout << e.message() << std::endl;
  }
  // ...
}

// Called when the game starts
void UMirrorCesiumStyleComponent::BeginPlay() {
  Super::BeginPlay();

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
bool UMirrorCesiumStyleComponent::Evaluate(const FString& expression) {

  FFunctionGraphTask::CreateAndDispatchWhenReady(
      [this, expression]() {
        if (!IsValid(Target.Get()) || !IsValid(this)) {
          return;
        }
        script::EngineScope enter(V8Engine.get());

        std::vector<script::Local<script::Value>> Metadatas =
            GetFeatureIDSetMetadataScriptValue();
        TArray<FColor> StyleColors;
        TArray<bool> StyleBools;
        StyleColors.Init(FColor(0, 0, 0, 0), Metadatas.size());
        StyleBools.Init(true, Metadatas.size());

        std::vector<script::Local<script::Value>> args;
        args.push_back(script::String::newString(TCHAR_TO_ANSI(*expression)));
        args.push_back(script::Array::newArray(Metadatas));
        script::Local<script::Value> ret;
        try {
          ret = V8Engine->get("Styling").asFunction().call({}, args);
          script::Local<script::Array> color =
              ret.asObject().get("color").asArray();
          script::Local<script::Array> show =
              ret.asObject().get("show").asArray();

          for (size_t i = 0; i < Metadatas.size(); i++) {
            StyleColors[i].R =
                color.get(i).asObject().get("red").asNumber().toDouble() * 255;
            StyleColors[i].G =
                color.get(i).asObject().get("green").asNumber().toDouble() *
                255;
            StyleColors[i].B =
                color.get(i).asObject().get("blue").asNumber().toDouble() * 255;
            StyleColors[i].A =
                color.get(i).asObject().get("alpha").asNumber().toDouble() *
                255;
            StyleBools[i] = show.get(i).asBoolean().value();
          }
          int TextureSize = 32;
          while (TextureSize < FMath::Sqrt(double(Metadatas.size()))) {
            TextureSize *= 2;
          }
          
          {
            UTexture2D* Texture = UTexture2D::CreateTransient(
                TextureSize,
                TextureSize,
                PF_B8G8R8A8);

            if (Texture) {
              void* Data =
                  Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
              FColor* Pixel = static_cast<FColor*>(Data);
              for (size_t i = 0; i < TextureSize * TextureSize; i++) {
                 *Pixel = FColor(0, 0, 0, 0);
                 ++Pixel;
               }
               Pixel = static_cast<FColor*>(Data);

              for (int32 Y = 0; Y < TextureSize; ++Y) {
                if (Y * TextureSize >= StyleColors.Num()) {
                  break;
                }

                for (int32 X = 0; X < TextureSize; ++X) {
                  if (Y * TextureSize + X >= StyleColors.Num()) {
                    break;
                  }
                  *Pixel = StyleColors[Y * TextureSize + X];
                  ++Pixel;
                }
              }

              Texture->PlatformData->Mips[0].BulkData.Unlock();

              AsyncTask(
                  ENamedThreads::GameThread,
                  [this, Texture]() {
                    Texture->UpdateResource();
                    if (!IsValid(Target.Get())) {
                      return;
                    }
                    UCesiumGltfPrimitiveComponent* GltfPrimitiveComponent =
                        Cast<UCesiumGltfPrimitiveComponent>(Target);
                    TArray<UMaterialInstanceDynamic*> DynamicInstanceMaterials =
                        GltfPrimitiveComponent->GetDynamicInstanceMaterials();
                    for (size_t i = 0; i < DynamicInstanceMaterials.Num();
                         i++) {
                      UCesiumMaterialUserData* pCesiumData =
                          GltfPrimitiveComponent->GetMaterialUserData(
                              DynamicInstanceMaterials[i]);
                      int32 index = -1;
                      if (pCesiumData && pCesiumData->LayerNames.Find(
                                             FString("StyleColor"),
                                             index)) {
                        DynamicInstanceMaterials[i]
                            ->SetTextureParameterValueByInfo(
                                FMaterialParameterInfo{
                                    FName("StyleColor"),
                                    EMaterialParameterAssociation::
                                        LayerParameter,
                                    index},
                                Texture);
                      }
                    }
                  });

            }
          }

          {
            UTexture2D* Texture = UTexture2D::CreateTransient(
                TextureSize,
                TextureSize,
                PF_B8G8R8A8);
            if (Texture) {
              void* Data =
                  Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
              FColor* Pixel = static_cast<FColor*>(Data);
              for (size_t i = 0; i < TextureSize * TextureSize; i++) {
                *Pixel = FColor(255, 255, 255, 255);
                ++Pixel;
              }
              Pixel = static_cast<FColor*>(Data);

              for (int32 Y = 0; Y < TextureSize; ++Y) {
                if (Y * TextureSize >= StyleBools.Num()) {
                  break;
                }
                for (int32 X = 0; X < TextureSize; ++X) {
                  if (Y * TextureSize + X >= StyleBools.Num()) {
                    break;
                  }
                  *Pixel = StyleBools[Y * TextureSize + X]
                               ? FColor(255, 255, 255, 255)
                                                    : FColor(0, 0, 0, 0);
                  ++Pixel;
                }
              }

              Texture->PlatformData->Mips[0].BulkData.Unlock();

              AsyncTask(
                  ENamedThreads::GameThread,
                  [this, Texture]() {
                    Texture->UpdateResource();
                    if (!IsValid(Target.Get())) {
                      return;
                    }
                    UCesiumGltfPrimitiveComponent* GltfPrimitiveComponent =
                        Cast<UCesiumGltfPrimitiveComponent>(Target);
                    TArray<UMaterialInstanceDynamic*> DynamicInstanceMaterials =
                        GltfPrimitiveComponent->GetDynamicInstanceMaterials();
                    for (size_t i = 0; i < DynamicInstanceMaterials.Num();
                         i++) {
                      UCesiumMaterialUserData* pCesiumData =
                          GltfPrimitiveComponent->GetMaterialUserData(
                              DynamicInstanceMaterials[i]);
                      int32 index = -1;
                      if (pCesiumData && pCesiumData->LayerNames.Find(
                                             FString("StyleVisible"),
                                             index)) {
                        DynamicInstanceMaterials[i]
                            ->SetTextureParameterValueByInfo(
                                FMaterialParameterInfo{
                                    FName("StyleVisible"),
                                    EMaterialParameterAssociation::
                                        LayerParameter,
                                    index},
                                Texture);
                      }
                    }
                  });

            }
          }
        } catch (const script::Exception& e) {
          std::cout << e.message() << std::endl;
        }
      },
      TStatId(),
      nullptr,
      ENamedThreads::AnyNormalThreadNormalTask);




  return true;
}

TArray<bool> UMirrorCesiumStyleComponent::ComputeExpressionBoolResult(
    const FString& Expression,
    const script::Local<script::Value>& arg) {
  using namespace script;
  std::vector<Local<Value>> args;
  args.push_back(String::newString(TCHAR_TO_ANSI(*Expression)));
  args.push_back(arg);
  Local<Value> ret =
      V8Engine->get("ComputeExpressionResult").asFunction().call({}, args);
  Local<Array> retArray = ret.asArray();
  TArray<bool> result;
  for (size_t i = 0; i < retArray.size(); i++) {
    result.Add(retArray.get(i).asBoolean().value());
  }
  
  return result;
}

TArray<FColor> UMirrorCesiumStyleComponent::ComputeExpressionColorResult(
    const FString& Expression,
    const script::Local<script::Value>& arg) {
  using namespace script;
  std::vector<Local<Value>> args;
  args.push_back(String::newString(TCHAR_TO_ANSI(*Expression)));
  args.push_back(arg);
  Local<Value> ret =
      V8Engine->get("ComputeExpressionResult").asFunction().call({}, args);

  Local<Array> retArray = ret.asArray();
  TArray<FColor> result;
  for (size_t i = 0; i < retArray.size(); i++) {
    Local<Object> temp = retArray.get(i).asObject();
    Local<Value> r = temp.get("r");
    Local<Value> g = temp.get("g");
    Local<Value> b = temp.get("b");
    Local<Value> a = temp.get("a");
    result.Add(FColor(
        r.asNumber().toDouble(),
        g.asNumber().toDouble(),
        b.asNumber().toDouble(),
        a.asNumber().toDouble()));
  }
  return result;
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

script::Local<script::Value>
UMirrorCesiumStyleComponent::CesiumMetadataToLocalValue(
    const FCesiumMetadataValue& Metadata) {
  ECesiumMetadataBlueprintType Type = UCesiumMetadataValueBlueprintLibrary::
      GetBlueprintType(Metadata);
  script::Local<script::Value> Value;
  switch (Type) {
  case ECesiumMetadataBlueprintType::None:
    break;
  case ECesiumMetadataBlueprintType::Boolean:
    Value = script::Boolean::newBoolean(
        UCesiumMetadataValueBlueprintLibrary::GetBoolean(Metadata, true));
    break;
  case ECesiumMetadataBlueprintType::Byte:
    Value = script::Number::newNumber(
        UCesiumMetadataValueBlueprintLibrary::GetByte(Metadata, 0));
    break;
  case ECesiumMetadataBlueprintType::Integer:
    Value = script::Number::newNumber(
        UCesiumMetadataValueBlueprintLibrary::GetInteger(Metadata, 0));
    break;
  case ECesiumMetadataBlueprintType::Integer64:
    Value = script::Number::newNumber(
        UCesiumMetadataValueBlueprintLibrary::GetInteger64(Metadata, 0));
    break;
  case ECesiumMetadataBlueprintType::Float:
    Value = script::Number::newNumber(
        UCesiumMetadataValueBlueprintLibrary::GetFloat(Metadata, 0));
    break;
  case ECesiumMetadataBlueprintType::Float64:
    Value = script::Number::newNumber(
        UCesiumMetadataValueBlueprintLibrary::GetFloat64(Metadata, 0));
    break;
  case ECesiumMetadataBlueprintType::IntPoint:
    UCesiumMetadataValueBlueprintLibrary::GetIntPoint(Metadata, FIntPoint());
    break;
  case ECesiumMetadataBlueprintType::Vector2D:
    UCesiumMetadataValueBlueprintLibrary::GetVector2D(Metadata, FIntPoint());
    break;
  case ECesiumMetadataBlueprintType::IntVector:
    UCesiumMetadataValueBlueprintLibrary::GetIntVector(Metadata, FIntVector());
    break;
  case ECesiumMetadataBlueprintType::Vector3f:
    UCesiumMetadataValueBlueprintLibrary::GetVector3f(Metadata, FVector3f());
    break;
  case ECesiumMetadataBlueprintType::Vector3:
    UCesiumMetadataValueBlueprintLibrary::GetVector(Metadata, FVector());
    break;
  case ECesiumMetadataBlueprintType::Vector4:
    UCesiumMetadataValueBlueprintLibrary::GetVector4(Metadata, FVector4());
    break;
  case ECesiumMetadataBlueprintType::Matrix:
    UCesiumMetadataValueBlueprintLibrary::GetMatrix( 
        Metadata,
       FMatrix::Identity);
    break;
  case ECesiumMetadataBlueprintType::String:
    Value = script::String::newString(
        TCHAR_TO_ANSI(*UCesiumMetadataValueBlueprintLibrary::GetString(
            Metadata,
            FString(""))));
    break;
  case ECesiumMetadataBlueprintType::Array:
    {
    FCesiumPropertyArray CesiumPropertyArray =
        UCesiumMetadataValueBlueprintLibrary::GetArray(Metadata);
    int64 ArraySize =
        UCesiumPropertyArrayBlueprintLibrary::GetArraySize(CesiumPropertyArray);
    std::vector<script::Local<script::Value>> result;
    for (int64 i = 0; i < ArraySize; i++) {
      FCesiumMetadataValue CesiumMetadataValue =
          UCesiumPropertyArrayBlueprintLibrary::GetValue(
              CesiumPropertyArray,
              i);
      script::Local<script::Value> Value =
          CesiumMetadataToLocalValue(CesiumMetadataValue);
      result.push_back(Value);
    }
    Value = script::Array::newArray(result);
    break;
    }
  default:
    break;
  }
  return Value;
}

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

    TMap<FString, FString> featureMetadata =
        UCesiumPropertyTableBlueprintLibrary::
            GetMetadataValuesForFeatureAsStrings(propertyTable, featureID);
    FeatureIDAndMetaDataJsonArray[featureID] = (
        ConvertTMapToJson(featureMetadata));
  }
  return FeatureIDAndMetaDataJsonArray;
}

std::vector<script::Local<script::Value>>
UMirrorCesiumStyleComponent::GetFeatureIDSetMetadataScriptValue() {
  UCesiumGltfPrimitiveComponent* GltfPrimitiveComponent =
      Cast<UCesiumGltfPrimitiveComponent>(Target);
  if (!GltfPrimitiveComponent ||
      !GltfPrimitiveComponent->IsValidLowLevelFast() ||
      GltfPrimitiveComponent->IsBeingDestroyed()) {
    return std::vector<script::Local<script::Value>>();
  }

  if (!GltfPrimitiveComponent->GetStaticMesh()) {
    return std::vector<script::Local<script::Value>>();
  }

  const FCesiumPrimitiveFeatures& features = GltfPrimitiveComponent->Features;
  const TArray<FCesiumFeatureIdSet>& featureIDSets =
      UCesiumPrimitiveFeaturesBlueprintLibrary::GetFeatureIDSets(features);
  if (FeatureIDSetIndex < 0 || FeatureIDSetIndex >= featureIDSets.Num()) {
    return std::vector<script::Local<script::Value>>();
  }
  const FCesiumFeatureIdSet& featureIDSet = featureIDSets[FeatureIDSetIndex];
  const int64 propertyTableIndex =
      UCesiumFeatureIdSetBlueprintLibrary::GetPropertyTableIndex(featureIDSet);
  auto count =
      UCesiumFeatureIdSetBlueprintLibrary::GetFeatureCount(featureIDSet);
  if (count <= 0) {
    return std::vector<script::Local<script::Value>>();
  }
  FCesiumModelMetadata Metadata;
  Metadata = UCesiumModelMetadataBlueprintLibrary::GetModelMetadata(
      GltfPrimitiveComponent);
  const TArray<FCesiumPropertyTable>& propertyTables =
      UCesiumModelMetadataBlueprintLibrary::GetPropertyTables(Metadata);
  if (propertyTableIndex < 0 || propertyTableIndex >= propertyTables.Num()) {
    return std::vector<script::Local<script::Value>>();
  }
  const FCesiumPropertyTable& propertyTable =
      propertyTables[propertyTableIndex];


  int64 FeatureIDCount = UCesiumFeatureIdSetBlueprintLibrary::GetFeatureCount(
      featureIDSets[FeatureIDSetIndex]);
  TMap<FString, FCesiumPropertyTableProperty> properties =
      UCesiumPropertyTableBlueprintLibrary::GetProperties(propertyTable);
  std::vector<script::Local<script::Value>> FeatureMetaDatas;
  for (int64 i = 0; i < FeatureIDCount; i++) {
    script::Local<script::Object> Obj = script::Object::newObject();
    for (auto property : properties) {
      Obj.set(
          script::String::newString(TCHAR_TO_ANSI(*property.Key)),
          CesiumMetadataToLocalValue(UCesiumPropertyTablePropertyBlueprintLibrary::
              GetValue(property.Value, i)));
    }
    FeatureMetaDatas.push_back(Obj);
  }

  return FeatureMetaDatas;
}

