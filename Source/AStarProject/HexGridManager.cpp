// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGridManager.h"
#include "HexTile.h"

// Sets default values
AHexGridManager::AHexGridManager()
{

}

// Called when the game starts or when spawned
void AHexGridManager::BeginPlay()
{
	Super::BeginPlay();
	
	HexGrid2DArray.SetNumZeroed(GridWidth);
	for (int32 i = 0; i < HexGrid2DArray.Num(); i++)
	{
		HexGrid2DArray[i].SetNumZeroed(GridHeight);
	}
	
	for (int32 y = 0; y < GridHeight; y++)
	{
		for (int32 x = 0; x < GridWidth; x++)
		{
			bool isGrass = true;

			const bool oddRow = y % 2 == 1; // Is current row an odd row?

			// If odd row shift right the half of the hexgrid width in x position
			const float xPos = oddRow ? (x * TileHorizontalOffset) + OddRowHorizontalOffset : x * TileHorizontalOffset; 
			const float yPos = y * TileVerticalOffset;

			TSubclassOf<AHexTile> tileToSpawn = GrassHexTile;
			if (FMath::RandRange(0.0f, 1.0f) <= ChanceOfWater && (x + y > 0))
			{
				tileToSpawn = WaterHexTile;
				isGrass = false;
			}


			AHexTile* newTile = GetWorld()->SpawnActor<AHexTile>(tileToSpawn, FVector(xPos,yPos,0), FRotator::ZeroRotator);
			newTile->TileIndex = FIntPoint(x, y);
			newTile->TileCost = isGrass ? 1.0f : 99999.0f;
			newTile->SetActorLabel(FString::Printf(TEXT("(%d,%d)_%0.1f"), x, y, (double)newTile->TileCost)); // For debug
			HexGrid2DArray[x][y] = newTile;
		}
	}
}


