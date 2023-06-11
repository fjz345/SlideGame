
#include "EditorBlueprintLibrary.h"

bool UEditorBlueprintLibrary::BrowseToAsset(UObject* Asset)
{
	TArray<UObject*> Objects;
	Objects.Add(Asset);
	GEditor->SyncBrowserToObjects(Objects);
	
	return true;
}