#include "SGGameMap.h"

#include "Math/RandomStream.h"

DEFINE_LOG_CATEGORY(LogGameMap);

FIntPoint MapGrid::From1DTo2DIndex(int32 Index) const
{
	return {Index % Dimensions.X, Index / Dimensions.X};
}

int32 MapGrid::From2DTo1DIndex(FIntPoint XY) const
{
	return XY.X + XY.Y * (Dimensions.X);
}

void MapGrid::Init(FVector2D InMinWorldBounds, FVector2D InMaxWorldBounds, FIntPoint InDimensions)
{
	WorldBounds[0] = InMinWorldBounds;
	WorldBounds[1] = InMaxWorldBounds;
	if (InDimensions.GetMax() > MAPGRID_MAXGRIDSIZE)
	{
		UE_LOG(LogGameMap, Error, TEXT("Failed to init MapGrid, GridSize (%d, %d) was greater than %d"), InDimensions.X, InDimensions.Y, MAPGRID_MAXGRIDSIZE);
		return;
	}
	Dimensions = InDimensions;
	CellGrid.SetNumUninitialized(Dimensions.X * Dimensions.Y);
	FPlatformMemory::Memset(CellGrid.GetData(), 0, sizeof(GridCell) * InDimensions.X * InDimensions.Y);

	ensure(Dimensions.X * Dimensions.Y == CellGrid.Num());
}

void MapGrid::InitToRenderTarget(FVector2D InMinWorldBounds, FVector2D InMaxWorldBounds, UTextureRenderTarget2D* InRenderTarget)
{
	Init(InMinWorldBounds, InMaxWorldBounds, 0);

	if (!InRenderTarget)
	{
		UE_LOG(LogGameMap, Error, TEXT("Failed to init MapGrid from render target"));
		return;
	}

	if (InRenderTarget->SizeX > MAPGRID_MAXGRIDSIZE || InRenderTarget->SizeY > MAPGRID_MAXGRIDSIZE)
	{
		UE_LOG(LogGameMap, Error, TEXT("Failed to init MapGrid from render target, size was to big"));
		return;
	}

	TArray<FLinearColor> Pixels;
	InRenderTarget->GetRenderTargetResource()->ReadLinearColorPixels(Pixels);

	TArray<GridCell> NewGridCells;
	for (int32 i = 0; i < Pixels.Num(); i++)
	{
		FLinearColor& CurrentPixel = Pixels[i];

		GridCell Cell{ CurrentPixel.R * 255.0f };
		NewGridCells.Emplace(Cell);
	}

	Dimensions = { Dimensions.X, Dimensions.Y };
	CellGrid.SetNumUninitialized(Dimensions.X * Dimensions.Y);
	FPlatformMemory::Memcpy(NewGridCells.GetData(), CellGrid.GetData(), sizeof(GridCell) * NewGridCells.Num());

	ensure(Dimensions.X * Dimensions.Y == CellGrid.Num());
}

#if WITH_EDITOR
void MapGrid::SetRandomValues()
{
	FRandomStream RandStream;
	int32 Num = Dimensions.X * Dimensions.Y;
	for (int32 i = 0; i < Num; i++)
	{
		uint8 RandomNumber = RandStream.RandRange(0, 255);
		GridCell Cell{ RandomNumber };
		FIntPoint Index = From1DTo2DIndex(i);
		WriteCellAt(Index, Cell);
	}
}
#endif

void MapGrid::WriteToRenderTarget(UTextureRenderTarget2D* InRenderTarget) const
{
}

int32 GenXDecimalNumber(int32 c, int32 n)
{
	if (n == 0 || c == 0)
	{
		return 0;
	}

	int32 counter = 0;
	int32 val = 1;
	for (int32 i = 1; i <= (n-1); i++)
	{
		val += FMath::Pow(10,i);
	}

	// 99....
	val *= c;

	return val;
}

void MapGrid::DebugPrint() const
{
#if WITH_EDITOR
	int32 Num = Dimensions.X * Dimensions.Y;
	// Printing more than this causes serious lag
	if (Num > 99999)
	{
		return;
	}

	UE_LOG(LogGameMap, Warning, TEXT("===========MapGrid::DebugPrint==========="));

	
	for (int32 i = 0; i < Num; i++)
	{
		FString OutputString = "";
		OutputString += "[";

		// Pretty printing
		{
			for (int32 j = 1; j < 10; j++)
			{
				int32 val = GenXDecimalNumber(9, j);

				if (val >= Num)
				{
					break;
				}

				if(i <= val)
				{
					OutputString += " ";
				}
			}
		}

		OutputString += FString::FromInt(i);
		OutputString += "]: ";

		GridCell cell = ReadCellAt(From1DTo2DIndex(i));

		OutputString += "Type: ";
		OutputString += FString::FromInt(cell.Type);
		OutputString += "\n";
		UE_LOG(LogGameMap, Warning, TEXT("%s"), *OutputString);
	}

	UE_LOG(LogGameMap, Warning, TEXT("========================================="));
#endif
}

GridCell MapGrid::ReadCellAt(FIntPoint xy) const
{
	if (IsIndexWithinGrid(xy))
	{
		return CellGrid[From2DTo1DIndex(xy)];
	}

#if WITH_EDITOR
	UE_LOG(LogGameMap, Warning, TEXT("MapGrid: Tried to read outside of bounds"));
#endif
	return GridCell{0};
}

void MapGrid::WriteCellAt(FIntPoint xy, GridCell val)
{
	if (IsIndexWithinGrid(xy))
	{
		CellGrid[From2DTo1DIndex(xy)] = val;
		return;
	}

#if WITH_EDITOR
	UE_LOG(LogGameMap, Warning, TEXT("MapGrid: Tried to write outside of bounds"));
#endif
}

FIntPoint MapGrid::GetCellIndexAt(FVector2D pos) const
{
	const float NormalizedX = FMath::Clamp(float(pos.X - WorldBounds[0].X) / (WorldBounds[1].X - WorldBounds[0].X), 0.0f, 1.0f);
	const float NormalizedY = FMath::Clamp(float(pos.Y - WorldBounds[0].Y) / (WorldBounds[1].Y - WorldBounds[0].Y), 0.0f, 1.0f);

	const int32 Idx = FMath::Floor(NormalizedX * (Dimensions.X - 1));
	const int32 Idy = FMath::Floor(NormalizedY * (Dimensions.Y - 1));

	return FIntPoint{ Idx, Idy };
}

bool MapGrid::IsIndexWithinGrid(FIntPoint XY) const
{
	return XY.X <= (Dimensions.X - 1) && XY.Y <= (Dimensions.Y - 1) && XY.X >= 0 && XY.Y >= 0;
}

void SGGameMap::Init()
{
	Grid.Init(FVector2D(-200.0), FVector2D(200.0), { 1024 , 1024 });
	Grid.DebugPrint();
}
