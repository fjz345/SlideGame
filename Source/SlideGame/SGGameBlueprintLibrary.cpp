#include "SGGameBlueprintLibrary.h"

#include "SlideGame.h"

USGGameBlueprintLibrary::USGGameBlueprintLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool USGGameBlueprintLibrary::RaytraceMap(const UObject* WorldContextObject, const FVector Start, const FVector End, EDrawDebugTrace::Type DrawDebugType, TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
	const ETraceTypeQuery TraceChannel = ETraceTypeQuery_Map;
	const TArray<AActor*> ActorsToIgnore;
	const bool bTraceComplex = true;
	const bool bIgnoreSelf = false;
	return UKismetSystemLibrary::LineTraceMulti(WorldContextObject, Start, End, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}