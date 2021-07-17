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

	const int Size = Chunk.GetDefaultObject()->Size;
	int ChunkCount = 0;

	if (Draw3D)
	{
		for (int x = -DrawDistance; x <= DrawDistance; x++)
		{
			for (int y = -DrawDistance; y <= DrawDistance; ++y)
			{
				for (int z = -DrawDistance; z <= DrawDistance; ++z)
				{
					GetWorld()->SpawnActor<AChunkBase>(
						Chunk,
						FVector(x * Size * 100, y * Size * 100, z * Size * 100),
						FRotator::ZeroRotator
					);

					ChunkCount++;
				}
			}
		}
	}
	else
	{
		for (int x = -DrawDistance; x <= DrawDistance; x++)
		{
			for (int y = -DrawDistance; y <= DrawDistance; ++y)
			{
				GetWorld()->SpawnActor<AChunkBase>(
					Chunk,
					FVector(x * Size * 100, y * Size * 100, 0),
					FRotator::ZeroRotator
				);

				ChunkCount++;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("%d Chunks Created"), ChunkCount);
}
