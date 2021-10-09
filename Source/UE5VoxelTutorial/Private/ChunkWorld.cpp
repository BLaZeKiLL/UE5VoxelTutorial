// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkWorld.h"

#include "ChunkBase.h"

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

	ChunkSize = Chunk.GetDefaultObject()->Size;

	switch (GenerationType)
	{
	case EGenerationType::GT_3D:
		Generate3DWorld();
		break;
	case EGenerationType::GT_2D:
		Generate2DWorld();
		break;
	default:
		throw std::invalid_argument("Invalid Generation Type");
	}

	UE_LOG(LogTemp, Warning, TEXT("%d Chunks Created"), ChunkCount);
}

void AChunkWorld::Generate3DWorld()
{
	for (int x = -DrawDistance; x <= DrawDistance; x++)
	{
		for (int y = -DrawDistance; y <= DrawDistance; ++y)
		{
			for (int z = -DrawDistance; z <= DrawDistance; ++z)
			{
				GetWorld()->SpawnActor<AChunkBase>(
					Chunk,
					FVector(x * ChunkSize * 100, y * ChunkSize * 100, z * ChunkSize * 100),
					FRotator::ZeroRotator
				);

				ChunkCount++;
			}
		}
	}
}

void AChunkWorld::Generate2DWorld()
{
	for (int x = -DrawDistance; x <= DrawDistance; x++)
	{
		for (int y = -DrawDistance; y <= DrawDistance; ++y)
		{
			GetWorld()->SpawnActor<AChunkBase>(
				Chunk,
				FVector(x * ChunkSize * 100, y * ChunkSize * 100, 0),
				FRotator::ZeroRotator
			);

			ChunkCount++;
		}
	}
}
