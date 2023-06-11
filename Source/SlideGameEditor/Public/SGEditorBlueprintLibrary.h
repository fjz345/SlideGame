#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "SGEditorBlueprintLibrary.generated.h"

UCLASS(meta = (ScriptName = "SGEditorBlueprintLibrary"))
class SLIDEGAMEEDITOR_API USGEditorBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Camera", meta = (Keywords = "unproject", WorldContext = "WorldContextObject"))
		static bool EditorGetCursorWorldLocationFromMousePos(UObject* WorldContextObject, FVector& WorldPosition, FVector& WorldDirection);

	UFUNCTION(BlueprintPure, Category = "Camera", meta = (Keywords = "unproject"))
		static bool EditorGetCameraLocation(FVector& WorldLocation);
};