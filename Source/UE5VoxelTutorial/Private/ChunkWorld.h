// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "GameFramework/Actor.h"
#include "ChunkWorld.generated.h"

class AChunkBase;

UCLASS()
class AChunkWorld final : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditInstanceOnly, Category="World")
	TSubclassOf<AChunkBase> ChunkType;
	
	UPROPERTY(EditInstanceOnly, Category="World")
	int DrawDistance = 5;

	UPROPERTY(EditInstanceOnly, Category="Chunk")
	TObjectPtr<UMaterialInterface> Material;
	
	UPROPERTY(EditInstanceOnly, Category="Chunk")
	int Size = 32;

	UPROPERTY(EditInstanceOnly, Category="Height Map")
	EGenerationType GenerationType;

	UPROPERTY(EditInstanceOnly, Category="Height Map")
	float Frequency = 0.03f;
	
	// Sets default values for this actor's properties
	AChunkWorld();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int ChunkCount;
	
	void Generate3DWorld();
	void Generate2DWorld();
};
