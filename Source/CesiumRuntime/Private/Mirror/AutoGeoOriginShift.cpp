// Fill out your copyright notice in the Description page of Project Settings.


#include "Mirror/AutoGeoOriginShift.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "CesiumRuntime.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Mirror/MirrorCoordinatesBPFuncLibrary.h"

FName AAutoGeoOriginShift::DEFAULT_ORIGINSHIFT_TAG =
    FName("DEFAULT_ORIGINSHIFT");
    // Sets default values
AAutoGeoOriginShift::AAutoGeoOriginShift()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    if (!this->ActorHasTag(DEFAULT_ORIGINSHIFT_TAG)) {
          this->Tags.Add(DEFAULT_ORIGINSHIFT_TAG);
    }
#if WITH_EDITOR
    FEditorDelegates::OnFocusViewportOnActors.AddUObject(
        this,
        &AAutoGeoOriginShift::ResetDelay);
#endif
}

// Called when the game starts or when spawned
void AAutoGeoOriginShift::BeginPlay()
{
  Super::BeginPlay();
  CesiumGeoreference = ACesiumGeoreference::GetDefaultGeoreference(this);
}

// Called every frame
void AAutoGeoOriginShift::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  if (AutoGeoOriginShiftEnable) {
    CalAutoShiftOrigin();
  }
  if (changeDelayTick > 0) {
    changeDelayTick--;
  }
}

void AAutoGeoOriginShift::SetAutoShiftGeoreference(
    ACesiumGeoreference* inGeoreference) {
  CesiumGeoreference = inGeoreference;
}

ACesiumGeoreference* AAutoGeoOriginShift::GetAutoShiftGeoreference() {
  return CesiumGeoreference;
}

bool AAutoGeoOriginShift::ShouldTickIfViewportsOnly() const { return true; }

AAutoGeoOriginShift*
AAutoGeoOriginShift::GetDefaultOriginShift(const UObject* WorldContextObject) {
  UWorld* world = WorldContextObject->GetWorld();
  // This method can be called by actors even when opening the content browser.
  if (!IsValid(world)) {
    return nullptr;
  }
  UE_LOG(
      LogCesium,
      Verbose,
      TEXT("World name for GetDefaultOriginShift: %s"),
      *world->GetFullName());

  // Note: The actor iterator will be created with the
  // "EActorIteratorFlags::SkipPendingKill" flag,
  // meaning that we don't have to handle objects
  // that have been deleted. (This is the default,
  // but made explicit here)
  AAutoGeoOriginShift* pOriginShift = nullptr;
  EActorIteratorFlags flags = EActorIteratorFlags::OnlyActiveLevels |
                              EActorIteratorFlags::SkipPendingKill;
  for (TActorIterator<AActor> actorIterator(
           world,
           AAutoGeoOriginShift::StaticClass(),
           flags);
       actorIterator;
       ++actorIterator) {
    AActor* actor = *actorIterator;
    if (actor->ActorHasTag(DEFAULT_ORIGINSHIFT_TAG)) {
      pOriginShift = Cast<AAutoGeoOriginShift>(actor);
      break;
    }
  }
  if (!pOriginShift) {
    // Legacy method of finding Georeference, for backwards compatibility with
    // existing projects
    AAutoGeoOriginShift* pGeoreferenceCandidate =
        FindObject<AAutoGeoOriginShift>(
            world->PersistentLevel,
            TEXT("CesiumOriginShiftDefault"));
    // Test if PendingKill
    if (IsValid(pGeoreferenceCandidate)) {
      pOriginShift = pGeoreferenceCandidate;
    }
  }
  if (!pOriginShift) {
    UE_LOG(
        LogCesium,
        Verbose,
        TEXT("Creating default Georeference for actor %s"),
        *WorldContextObject->GetName());
    // Spawn georeference in the persistent level
    FActorSpawnParameters spawnParameters;
    spawnParameters.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    pOriginShift = world->SpawnActor<AAutoGeoOriginShift>(spawnParameters);
    // Null check so the editor doesn't crash when it makes arbitrary calls to
    // this function without a valid world context object.
    if (pOriginShift) {
      pOriginShift->Tags.Add(DEFAULT_ORIGINSHIFT_TAG);
    }

  } else {
    UE_LOG(
        LogCesium,
        Verbose,
        TEXT("Using existing Georeference %s for actor %s"),
        *pOriginShift->GetName(),
        *WorldContextObject->GetName());
  }
  return pOriginShift;
}

FVector AAutoGeoOriginShift::CalAutoShiftOrigin()
{

  FVector ViewECEFPosition  =
      UMirrorCoordinatesBPFuncLibrary::UnrealToECEFTransform(
          UMirrorCoordinatesBPFuncLibrary::GetCameraTransform(GetWorld()))
          .GetLocation();

  FVector CameraInLonLatH =
      UMirrorCoordinatesBPFuncLibrary::ECEFToLonLatH(ViewECEFPosition);


  //GEngine->AddOnScreenDebugMessage(
  //    -1,
  //    3,
  //    FColor::Cyan,
  //    CameraInLonLatH.ToString());

  //if (firstTimeShift) {
  //  firstTimeShift = false;
  //  return ShiftOrigin;
  //}


  AutoShiftLevel = 10 - FMath::Clamp(abs(CameraInLonLatH.Z) / 20000.f, 0, 8);
  AutoShiftLevel = 10;
  CameraInLonLatH.Z = 0;
  if (FVector::Distance(FVector(CameraInLonLatH.X, CameraInLonLatH.Y,0), FVector(ShiftOrigin.X, ShiftOrigin.Y, 0)) >
          (180.f / pow(2, AutoShiftLevel)) ||
      firstTimeShift
    ) {
    if (changeDelayTick <= 0) {
      firstTimeShift = false;
      ChangeOrigin(CameraInLonLatH);
    }
  }




  return ShiftOrigin;
}

void AAutoGeoOriginShift::ChangeOrigin(const FVector& CameraInLonLatH) {
  FTransform LastECEFTransform =
      UMirrorCoordinatesBPFuncLibrary::GetUnrealToECEFTransform();
  CesiumGeoreference->SetOriginLongitudeLatitudeHeight(CameraInLonLatH);
  ShiftOrigin = CameraInLonLatH;
  GeoreferenceOriginChangeDelegate.Broadcast(
      UMirrorCoordinatesBPFuncLibrary::GetECEFToUnrealTransform());

  UMaterialParameterCollection* ParameterCollection = LoadObject<
      UMaterialParameterCollection>(
      GWorld,
      TEXT(
          "/Script/Engine.MaterialParameterCollection'/CesiumForUnreal/Materials/MegaParam.MegaParam'"));

  UMaterialParameterCollectionInstance* ParameterCollectionInstance =
      GWorld->GetParameterCollectionInstance(ParameterCollection);
  //===================UnrealToECEF============================
  // FMatrix44f UnrealToECEF = (FMatrix44f)UMegaGeoreferenceBlueprintLibrary::
  //    GetUnrealToCesiumGeoreferenceECEFTransform().ToMatrixWithScale();
  ////UnrealToECEF = UnrealToECEF.GetTransposed();
  // FVector4f UnrealToECEFRow0{
  //     UnrealToECEF.M[0][0],
  //     UnrealToECEF.M[0][1],
  //     UnrealToECEF.M[0][2],
  //     UnrealToECEF.M[0][3]};

  // FVector4f UnrealToECEFRow1{
  //     UnrealToECEF.M[1][0],
  //     UnrealToECEF.M[1][1],
  //     UnrealToECEF.M[1][2],
  //     UnrealToECEF.M[1][3]};

  // FVector4f UnrealToECEFRow2{
  //     UnrealToECEF.M[2][0],
  //     UnrealToECEF.M[2][1],
  //     UnrealToECEF.M[2][2],
  //     UnrealToECEF.M[2][3]};

  // FVector4f UnrealToECEFRow3{
  //     UnrealToECEF.M[3][0],
  //     UnrealToECEF.M[3][1],
  //     UnrealToECEF.M[3][2],
  //     UnrealToECEF.M[3][3]};

  // ParameterCollectionInstance->SetVectorParameterValue(
  //     FName("UnrealToECEFMatrixRow1"),
  //     UnrealToECEFRow0);
  // ParameterCollectionInstance->SetVectorParameterValue(
  //     FName("UnrealToECEFMatrixRow2"),
  //     UnrealToECEFRow1);
  // ParameterCollectionInstance->SetVectorParameterValue(
  //     FName("UnrealToECEFMatrixRow3"),
  //     UnrealToECEFRow2);
  // ParameterCollectionInstance->SetVectorParameterValue(
  //     FName("UnrealToECEFMatrixRow4"),
  //     UnrealToECEFRow3);

  ////=================ECEFToUnreal======================
  // FMatrix44f ECEFToUnreal = (FMatrix44f)UMegaGeoreferenceBlueprintLibrary::
  //     GetCesiumGeoreferenceECEFToUnrealTransform().ToMatrixWithScale();
  ////ECEFToUnreal = ECEFToUnreal.GetTransposed();

  // FVector4f ECEFToUnrealRow0{
  //     ECEFToUnreal.M[0][0],
  //     ECEFToUnreal.M[0][1],
  //     ECEFToUnreal.M[0][2],
  //     ECEFToUnreal.M[0][3]};

  // FVector4f ECEFToUnrealRow1{
  //     ECEFToUnreal.M[1][0],
  //     ECEFToUnreal.M[1][1],
  //     ECEFToUnreal.M[1][2],
  //     ECEFToUnreal.M[1][3]};

  // FVector4f ECEFToUnrealRow2{
  //     ECEFToUnreal.M[2][0],
  //     ECEFToUnreal.M[2][1],
  //     ECEFToUnreal.M[2][2],
  //     ECEFToUnreal.M[2][3]};

  // FVector4f ECEFToUnrealRow3{
  //     ECEFToUnreal.M[3][0],
  //     ECEFToUnreal.M[3][1],
  //     ECEFToUnreal.M[3][2],
  //     ECEFToUnreal.M[3][3]};

  // ParameterCollectionInstance->SetVectorParameterValue(
  //     FName("ECEFToUnrealMatrixRow1"),
  //     ECEFToUnrealRow0);
  // ParameterCollectionInstance->SetVectorParameterValue(
  //     FName("ECEFToUnrealMatrixRow2"),
  //     ECEFToUnrealRow1);
  // ParameterCollectionInstance->SetVectorParameterValue(
  //     FName("ECEFToUnrealMatrixRow3"),
  //     ECEFToUnrealRow2);
  // ParameterCollectionInstance->SetVectorParameterValue(
  //     FName("ECEFToUnrealMatrixRow4"),
  //     ECEFToUnrealRow3);

  if (UMirrorCoordinatesBPFuncLibrary::IsInEditorMode() &&
      !UMirrorCoordinatesBPFuncLibrary::IsInEditorPlayMode()) {
#if WITH_EDITOR
    if (GEditor && GEditor->GetActiveViewport()) {
      FEditorViewportClient* EditorViewportClient =
          static_cast<FEditorViewportClient*>(
              GEditor->GetActiveViewport()->GetClient());

      if (EditorViewportClient) {
        FVector ECEFLocation = LastECEFTransform.TransformPosition(
            EditorViewportClient->GetViewLocation());

        EditorViewportClient->SetViewLocation(
            UMirrorCoordinatesBPFuncLibrary::GetECEFToUnrealTransform()
                .TransformPosition(ECEFLocation));

        FTransform temp = LastECEFTransform;
        temp.SetScale3D(LastECEFTransform.GetScale3D().GetAbs());

        FQuat ECEFRotation = temp.TransformRotation(
            EditorViewportClient->GetViewRotation().Quaternion());

        FVector EditorLocation = EditorViewportClient->GetViewLocation();
        FRotator EditorRotation = EditorViewportClient->GetViewRotation();
        FTransform EditorTransform;
        EditorTransform.SetLocation(EditorLocation);
        EditorTransform.SetRotation(EditorRotation.Quaternion());

        FTransform AfterEditorTransform =
            UMirrorCoordinatesBPFuncLibrary::GetECEFToUnrealTransform() *
            LastECEFTransform * EditorTransform;

        EditorViewportClient->SetViewLocation(
            AfterEditorTransform.GetLocation());

     /*    EditorViewportClient->SetViewRotation(
             AfterEditorTransform.GetRotation().Rotator());*/
      }
    }
#endif
  }
}

void AAutoGeoOriginShift::ResetDelay(const TArray<AActor*>& actor) {
  changeDelayTick = 20;
}

