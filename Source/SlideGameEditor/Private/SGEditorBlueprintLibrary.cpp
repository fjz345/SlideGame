#include "SGEditorBlueprintLibrary.h"

#include "Editor/EditorEngine.h"


bool USGEditorBlueprintLibrary::EditorDeprojectScreenToWorld(const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection)
{



	if (GIsEditor)
	{
		FTransform EditorViewportTransform;
		GEditor->GetSimulateInEditorViewTransform(EditorViewportTransform);
		FSceneViewProjectionData ProjectionData;

		FViewport* ActiveViewport = GEditor->GetActiveViewport();
		
		int32 SizeX = ActiveViewport->GetSizeXY().X;
		int32 SizeY = ActiveViewport->GetSizeXY().Y;

		int32 X = SizeX;
		int32 Y = SizeY;



		X += ActiveViewport->GetInitialPositionXY().X;
		Y += ActiveViewport->GetInitialPositionXY().Y;

		FIntRect UnconstrainedRectangle = FIntRect(X, Y, X + SizeX, Y + SizeY);
		{
			FMatrix const InvViewProjMatrix = EditorViewportTransform.ToMatrixWithScale().InverseFast();
			FSceneView::DeprojectScreenToWorld(ScreenPosition, UnconstrainedRectangle, InvViewProjMatrix, /*out*/ WorldPosition, /*out*/ WorldDirection);
			return true;
		}
	}

	// something went wrong, zero things and return false
	WorldPosition = FVector::ZeroVector;
	WorldDirection = FVector::ZeroVector;
	return false;
}