// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/TextureRenderTarget2D.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGameMap, Log, All);

struct GridCell
{
public:
	GridCell() = default;
	uint8 Type = 0;

private:

};

class MapGrid
{

public:
	MapGrid() = default;

	void Init(FVector2D InMinWorldBounds, FVector2D InMaxWorldBounds, FIntPoint InDimensions);
	void InitToRenderTarget(FVector2D InMinWorldBounds, FVector2D InMaxWorldBounds, UTextureRenderTarget2D* InRenderTarget);
	
#if WITH_EDITOR
	void SetRandomValues();
#endif

	void WriteToRenderTarget(UTextureRenderTarget2D* InRenderTarget) const;
		
	void DebugPrint() const;

private:
	GridCell ReadCellAt(FIntPoint xy) const;
	void WriteCellAt(FIntPoint xy, GridCell val);
	FIntPoint GetCellIndexAt(FVector2D pos) const;

	FIntPoint From1DTo2DIndex(int32 Index) const;
	int32 From2DTo1DIndex(FIntPoint XY) const;
	bool IsIndexWithinGrid(FIntPoint XY) const;

	// min/max
	FVector2D WorldBounds[2] = { FVector2D::ZeroVector };
#define MAPGRID_MAXGRIDSIZE 4096
	FIntPoint Dimensions{ 0,0 };
	TArray<GridCell, TFixedAllocator<MAPGRID_MAXGRIDSIZE * MAPGRID_MAXGRIDSIZE>> CellGrid;
};

class SGGameMap
{
public:
	void Init();

private:
	MapGrid Grid{};
};