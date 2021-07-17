// Fill out your copyright notice in the Description page of Project Settings.


#include "MarchingChunk.h"

#include "ProceduralMeshComponent.h"
#include "FastNoiseLite.h"

// Sets default values
AMarchingChunk::AMarchingChunk()
{
	// Initialize Voxels
	Voxels.SetNum((Size + 1) * (Size + 1) * (Size + 1));
}

// Called when the game starts or when spawned
void AMarchingChunk::BeginPlay()
{
	Super::BeginPlay();
}

void AMarchingChunk::GenerateHeightMap()
{
	Generate3DHeightMap(GetActorLocation() / 100);
}

void AMarchingChunk::Generate2DHeightMap(const FVector Position)
{
	for (int x = 0; x <= Size; ++x)
	{
		for (int y = 0; y <= Size; ++y)
		{
			const float Xpos = x * Position.X;
			const float ypos = y * Position.Y;
			
			const int Height = FMath::Clamp(FMath::RoundToInt((Noise->GetNoise(Xpos, ypos) + 1) * Size / 2), 0, Size);

			for (int z = 0; z < Height; z++)
			{
				Voxels[GetVoxelIndex(x,y,z)] = 1.0f;
			}

			for (int z = Height; z < Size; z++)
			{
				Voxels[GetVoxelIndex(x,y,z)] = -1.0f;
			}
		}
	}
}

void AMarchingChunk::Generate3DHeightMap(const FVector Position)
{	
	for (int x = 0; x <= Size; ++x)
	{
		for (int y = 0; y <= Size; ++y)
		{
			for (int z = 0; z <= Size; ++z)
			{
				Voxels[GetVoxelIndex(x,y,z)] = Noise->GetNoise(x + Position.X, y + Position.Y, z + Position.Z);	
			}
		}
	}
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

void AMarchingChunk::March(const int X, const int Y, const int Z, const float Cube[8])
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
			const float Offset = Interpolation ? GetInterpolationOffset(Cube[EdgeConnection[i][0]], Cube[EdgeConnection[i][1]]) : 0.5f;

			EdgeVertex[i].X = X + (VertexOffset[EdgeConnection[i][0]][0] + Offset * EdgeDirection[i][0]);
			EdgeVertex[i].Y = Y + (VertexOffset[EdgeConnection[i][0]][1] + Offset * EdgeDirection[i][1]);
			EdgeVertex[i].Z = Z + (VertexOffset[EdgeConnection[i][0]][2] + Offset * EdgeDirection[i][2]);
		}
	}

	// Save triangles, at most can be 5
	for (int i = 0; i < 5; ++i)
	{
		if (TriangleConnectionTable[VertexMask][3 * i] < 0) break;

		auto V1 = EdgeVertex[TriangleConnectionTable[VertexMask][3 * i]] * 100;
		auto V2 = EdgeVertex[TriangleConnectionTable[VertexMask][3 * i + 1]] * 100;
		auto V3 = EdgeVertex[TriangleConnectionTable[VertexMask][3 * i + 2]] * 100;

		auto Normal = FVector::CrossProduct(V2 - V1, V3 - V1);
		Normal.Normalize();

		MeshData.Vertices.Add(V1);
		MeshData.Vertices.Add(V2);
		MeshData.Vertices.Add(V3);

		MeshData.Triangles.Add(VertexCount + TriangleOrder[0]);
		MeshData.Triangles.Add(VertexCount + TriangleOrder[1]);
		MeshData.Triangles.Add(VertexCount + TriangleOrder[2]);

		MeshData.Normals.Add(Normal);
		MeshData.Normals.Add(Normal);
		MeshData.Normals.Add(Normal);

		VertexCount += 3;
	}
}

int AMarchingChunk::GetVoxelIndex(const int X, const int Y, const int Z) const
{
	return Z * (Size + 1) * (Size + 1) + Y * (Size + 1) + X;
}

float AMarchingChunk::GetInterpolationOffset(const float V1, const float V2) const
{
	const float Delta = V2 - V1;
	return Delta == 0.0f ? SurfaceLevel : (SurfaceLevel - V1) / Delta;
}
