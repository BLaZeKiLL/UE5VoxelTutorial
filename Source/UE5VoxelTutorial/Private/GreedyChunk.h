// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ChunkBase.h"
#include "Enums.h"
#include "GreedyChunk.generated.h"

class FastNoiseLite;
class UProceduralMeshComponent;

UCLASS()
class AGreedyChunk final : public AChunkBase
{
	GENERATED_BODY()

	struct FMask
	{
		EBlock Block;
		int Normal;
	};

public:	
	// Sets default values for this actor's properties
	AGreedyChunk();
	
	UPROPERTY(EditDefaultsOnly, Category="Height Map")
	EGenerationType GenerationType;
	
protected:
	virtual void GenerateHeightMap() override;
	
	virtual void GenerateMesh() override;

private:
	TArray<EBlock> Blocks;

	void Generate2DHeightMap(FVector Position);
	
	void Generate3DHeightMap(FVector Position);
	
	void CreateQuad(FMask Mask, FIntVector AxisMask, int Width, int Height, FIntVector V1, FIntVector V2, FIntVector V3, FIntVector V4);

	int GetBlockIndex(int X, int Y, int Z) const;

	EBlock GetBlock(FIntVector Index) const;

	bool CompareMask(FMask M1, FMask M2) const;
};


