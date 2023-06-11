// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGGameState.h"

#include "SlideGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SLIDEGAME_API ASlideGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitGameState() override;

private:
	SGGameState GameplayState{};
};
