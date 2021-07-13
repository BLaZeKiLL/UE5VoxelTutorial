// Fill out your copyright notice in the Description page of Project Settings.


#include "MarchingChunk.h"

#include "ProceduralMeshComponent.h"
#include "FastNoiseLite.h"

// Sets default values
AMarchingChunk::AMarchingChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh");
	Noise = new FastNoiseLite();
	Noise->SetFrequency(0.03f);
	Noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	Noise->SetFractalType(FastNoiseLite::FractalType_FBm);

	// Initialize Blocks
	Voxels.SetNum((Size + 1) * (Size + 1) * (Size + 1));

	// Mesh Settings
	Mesh->SetCastShadow(false);

	// Set Mesh as root
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void AMarchingChunk::BeginPlay()
{
	Super::BeginPlay();

	GenerateVoxels();

	GenerateMesh();

	UE_LOG(LogTemp, Warning, TEXT("Vertex Count : %d"), VertexCount);
	
	ApplyMesh();
}

void AMarchingChunk::GenerateVoxels()
{
	const auto Location = GetActorLocation();

	for (int x = 0; x <= Size; ++x)
	{
		for (int y = 0; y <= Size; ++y)
		{
			for (int z = 0; z <= Size; ++z)
			{
				const float Xpos = (x * 100 + Location.X) / 100;
				const float Ypos = (y * 100 + Location.Y) / 100;
				const float Zpos = (z * 100 + Location.Z) / 100;

				Voxels[GetVoxelIndex(x,y,z)] = Noise->GetNoise(Xpos, Ypos, Zpos);
			}
		}
	}
}

void AMarchingChunk::ApplyMesh()
{
	Mesh->CreateMeshSection(0, MeshData.Vertices, MeshData.Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), false);
}

void AMarchingChunk::GenerateMesh()
{
	// Triangulation order
	if (SurfaceLevel > 0.0f)
	{
		TriangleOrder[0] = 0;
		TriangleOrder[1] = 1;
		TriangleOrder[2] = 2;
	}
	else
	{
		TriangleOrder[0] = 2;
		TriangleOrder[1] = 1;
		TriangleOrder[2] = 0;
	}

	float Cube[8];
	
	for (int X = 0; X < Size; ++X)
	{
		for (int Y = 0; Y < Size; ++Y)
		{
			for (int Z = 0; Z < Size; ++Z)
			{
				for (int i = 0; i < 8; ++i)
				{
					Cube[i] = Voxels[GetVoxelIndex(X + VertexOffset[i][0],Y + VertexOffset[i][1],Z + VertexOffset[i][2])];
				}

				March(X,Y,Z, Cube);
			}
		}
	}
}

void AMarchingChunk::March(const int X, const int Y, const int Z, const float Cube[])
{
	int VertexMask = 0;
	FVector EdgeVertex[12];

	//Find which vertices are inside of the surface and which are outside
	for (int i = 0; i < 8; ++i)
	{
		if (Cube[i] <= SurfaceLevel) VertexMask |= 1 << i;
	}

	const int EdgeMask = CubeEdgeFlags[VertexMask];
	
	if (EdgeMask == 0) return;
	
	// Find intersection points
	for (int i = 0; i < 12; ++i)
	{
		if ((EdgeMask & 1 << i) != 0)
		{
			const float Offset = GetInterpolationOffset(Cube[EdgeConnection[i][0]], Cube[EdgeConnection[i][1]]);

			EdgeVertex[i].X = X + (VertexOffset[EdgeConnection[i][0]][0] + Offset * EdgeDirection[i][0]);
			EdgeVertex[i].Y = Y + (VertexOffset[EdgeConnection[i][0]][1] + Offset * EdgeDirection[i][1]);
			EdgeVertex[i].Z = Z + (VertexOffset[EdgeConnection[i][0]][2] + Offset * EdgeDirection[i][2]);
		}
	}

	// Save triangles, at most can be 5
	for (int i = 0; i < 5; ++i)
	{
		if (TriangleConnectionTable[VertexMask][3 * i] < 0) break;
		
		for (int j = 0; j < 3; ++j)
		{
			MeshData.Triangles.Add(VertexCount + TriangleOrder[j]);
			MeshData.Vertices.Add(EdgeVertex[TriangleConnectionTable[VertexMask][3 * i + j]] * 100);
		}

		VertexCount += 3;
	}
}

int AMarchingChunk::GetVoxelIndex(const int X, const int Y, const int Z) const
{
	return Z * Size * Size + Y * Size + X;
}

float AMarchingChunk::GetInterpolationOffset(const float V1, const float V2) const
{
	const float Delta = V2 - V1;
	return Delta == 0.0f ? SurfaceLevel : (SurfaceLevel - V1) / Delta;
}
