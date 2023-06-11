#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "SGEditorBlueprintLibrary.generated.h"

UCLASS(meta = (ScriptName = "EditorBlueprintLibrary"))
class SLIDEGAMEEDITOR_API USGEditorBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Camera", meta = (Keywords = "unproject"))
		static bool EditorDeprojectScreenToWorld(const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection);
};