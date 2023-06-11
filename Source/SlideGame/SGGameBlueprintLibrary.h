#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "SGGameBlueprintLibrary.generated.h"

UCLASS(meta = (ScriptName = "GameBlueprintLibrary"))
class SLIDEGAME_API USGGameBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/** Returns true if the attribute actually exists */
	UFUNCTION(BlueprintCallable, Category = "Game|Map", meta = (WorldContext = "WorldContextObject"))
		static bool RaytraceMap(const UObject* WorldContextObject, const FVector Start, const FVector End, EDrawDebugTrace::Type DrawDebugType, TArray<FHitResult>& OutHits, FLinearColor TraceColor = FLinearColor::Yellow, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);
};