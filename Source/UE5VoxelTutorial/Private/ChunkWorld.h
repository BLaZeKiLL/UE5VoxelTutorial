// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "GameFramework/Actor.h"
#include "ChunkWorld.generated.h"

class AChunkBase;

UCLASS()
class AChunkWorld : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditInstanceOnly, Category="Chunk World")
	TSubclassOf<AChunkBase> Chunk;

	UPROPERTY(EditInstanceOnly, Category="Chunk World")
	EGenerationType GenerationType;
	
	UPROPERTY(EditInstanceOnly, Category="Chunk World")
	int DrawDistance = 5;
	
	// Sets default values for this actor's properties
	AChunkWorld();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int ChunkCount;
	int ChunkSize;
	
	void Generate3DWorld();
	void Generate2DWorld();
};
