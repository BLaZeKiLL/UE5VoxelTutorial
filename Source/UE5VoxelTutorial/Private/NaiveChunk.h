// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ChunkBase.h"
#include "GameFramework/Actor.h"
#include "NaiveChunk.generated.h"

enum class EBlock;
enum class EDirection;
class FastNoiseLite;
class UProceduralMeshComponent;

UCLASS()
class ANaiveChunk final : public AChunkBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANaiveChunk();

protected:
	virtual void GenerateHeightMap() override;

	virtual void GenerateMesh() override;

private:
	TArray<EBlock> Blocks;

	const FVector BlockVertexData[8] = {
		FVector(100,100,100),
		FVector(100,0,100),
		FVector(100,0,0),
		FVector(100,100,0),
		FVector(0,0,100),
		FVector(0,100,100),
		FVector(0,100,0),
		FVector(0,0,0)
	};

	const int BlockTriangleData[24] = {
		0,1,2,3, // Forward
		5,0,3,6, // Right
		4,5,6,7, // Back
		1,4,7,2, // Left
		5,4,1,0, // Up
		3,2,7,6  // Down
	};


	
	bool Check(FVector Position) const;
	
	void CreateFace(EDirection Direction, FVector Position);

	TArray<FVector> GetFaceVertices(EDirection Direction, FVector Position) const;

	FVector GetPositionInDirection(EDirection Direction, FVector Position) const;
	
	int GetBlockIndex(int X, int Y, int Z) const;
};
