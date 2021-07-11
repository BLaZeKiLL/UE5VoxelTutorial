// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MarchingChunk.generated.h"

UCLASS()
class AMarchingChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMarchingChunk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
