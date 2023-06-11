// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Map/SGGameMap.h"

class SGGameState
{
public:
	void Init();
private:

	SGGameMap Map{};
};