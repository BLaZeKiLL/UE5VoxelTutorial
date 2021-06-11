// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkWorld.h"


// Sets default values
AChunkWorld::AChunkWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AChunkWorld::BeginPlay()
{
	Super::BeginPlay();

	for (int x = -DrawDistance; x <= DrawDistance; x++)
	{
		for (int y = -DrawDistance; y < DrawDistance; ++y)
		{
			GetWorld()->SpawnActor<AActor>(
				Chunk,
				FVector(x * ChunkSize * 100, y * ChunkSize * 100, 0),
				FRotator::ZeroRotator
			);
		}
	}	
}
