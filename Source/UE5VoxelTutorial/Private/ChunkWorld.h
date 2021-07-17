// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkWorld.generated.h"

class AChunkBase;

UCLASS()
class AChunkWorld : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Chunk World")
	TSubclassOf<AChunkBase> Chunk;
	
	UPROPERTY(EditAnywhere, Category="Chunk World")
	int DrawDistance = 5;
	
	// Sets default values for this actor's properties
	AChunkWorld();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
