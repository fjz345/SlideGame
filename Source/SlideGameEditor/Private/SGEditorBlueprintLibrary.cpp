#include "SGEditorBlueprintLibrary.h"

#include "Editor/EditorEngine.h"
#include "Kismet/GameplayStatics.h"
#include "LevelEditorViewport.h"
#include "Slate/SceneViewport.h"


bool USGEditorBlueprintLibrary::EditorGetCursorWorldLocationFromMousePos(UObject* WorldContextObject, FVector& WorldPosition, FVector& WorldDirection)
{
	const TArray<class FLevelEditorViewportClient*>& clients = GEditor->GetLevelViewportClients();

	FLevelEditorViewportClient* FoundClient = nullptr;
	for (auto& EditorViewportClient : clients)
	{
		if (EditorViewportClient->GetWorld() == WorldContextObject->GetWorld())
		{
			FoundClient = EditorViewportClient;
		}
	}

	if (FoundClient)
	{
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			FoundClient->Viewport,
			FoundClient->GetScene(),
			FoundClient->EngineShowFlags).SetRealtimeUpdate(FoundClient->IsRealtime()));		// why SetRealtimeUpdate here??
		FSceneView* View = FoundClient->CalcSceneView(&ViewFamily);

		WorldPosition = FoundClient->GetCursorWorldLocationFromMousePos().GetOrigin();
		WorldDirection = FoundClient->GetCursorWorldLocationFromMousePos().GetDirection();
		return true;
	}

	// something went wrong, zero things and return false
	WorldPosition = FVector::ZeroVector;
	WorldDirection = FVector::ZeroVector;
	return false;
}

bool USGEditorBlueprintLibrary::EditorGetCameraLocation(FVector& WorldLocation)
{
	const TArray<class FLevelEditorViewportClient*>& clients = GEditor->GetLevelViewportClients();

	FLevelEditorViewportClient* FoundClient = nullptr;
	for (auto& EditorViewportClient : clients)
	{
		if (EditorViewportClient->IsSimulateInEditorViewport())
		{
			FoundClient = EditorViewportClient;
		}
	}

	if (FoundClient)
	{
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			FoundClient->Viewport,
			FoundClient->GetScene(),
			FoundClient->EngineShowFlags).SetRealtimeUpdate(FoundClient->IsRealtime()));		// why SetRealtimeUpdate here??
		FSceneView* View = FoundClient->CalcSceneView(&ViewFamily);
		WorldLocation = View->ViewMatrices.GetViewOrigin();
		return true;
	}

	WorldLocation = { 0.0, 0.0, 0.0 };
	return false;
}
