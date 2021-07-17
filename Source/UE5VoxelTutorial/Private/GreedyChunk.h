// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ChunkBase.h"
#include "ChunkMeshData.h"
#include "GameFramework/Actor.h"
#include "GreedyChunk.generated.h"

enum class EBlock;
enum class EDirection;
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GenerateHeightMap() override;
	
	virtual void GenerateMesh() override;

private:
	TArray<EBlock> Blocks;

	void CreateQuad(FMask Mask, FIntVector AxisMask, FIntVector V1, FIntVector V2, FIntVector V3, FIntVector V4);

	int GetBlockIndex(int X, int Y, int Z) const;

	EBlock GetBlock(FIntVector Index) const;

	bool CompareMask(FMask M1, FMask M2) const;
};


