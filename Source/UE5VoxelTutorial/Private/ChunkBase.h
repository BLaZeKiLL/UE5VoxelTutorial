// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChunkMeshData.h"
#include "GameFramework/Actor.h"
#include "ChunkBase.generated.h"

class FastNoiseLite;
class UProceduralMeshComponent;

UCLASS(Abstract)
class UE5VOXELTUTORIAL_API AChunkBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChunkBase();

	UPROPERTY(EditDefaultsOnly, Category="Chunk")
	int Size = 64;

	UPROPERTY(EditDefaultsOnly, Category="HeightMap")
	float Frequency = 0.03f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GenerateHeightMap();

	virtual void GenerateMesh();

	TObjectPtr<UProceduralMeshComponent> Mesh;
	FastNoiseLite* Noise;
	FChunkMeshData MeshData;
	int VertexCount = 0;

private:
	void ApplyMesh() const;
};
