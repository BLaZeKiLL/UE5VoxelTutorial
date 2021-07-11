// Fill out your copyright notice in the Description page of Project Settings.


#include "MarchingChunk.h"

// Sets default values
AMarchingChunk::AMarchingChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMarchingChunk::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMarchingChunk::GenerateBlocks()
{
}

void AMarchingChunk::ApplyMesh()
{
}

void AMarchingChunk::GenerateMesh()
{
}
