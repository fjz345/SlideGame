
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "EditorBlueprintLibrary.generated.h"

UCLASS()
class SLIDEGAMEEDITOR_API UEditorBlueprintLibrary :
    public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    /** Tells the content browser to browse to the asset */
    UFUNCTION(BlueprintCallable, Category = "Content Browser")
    static bool BrowseToAsset(UObject* Asset);

};