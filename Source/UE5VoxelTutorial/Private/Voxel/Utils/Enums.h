#pragma once

enum class EDirection : uint8
{
	Forward, Right, Back, Left, Up, Down
};

enum class EBlock : uint8
{
	Null, Air, Stone, Dirt, Grass
};

UENUM(BlueprintType)
enum class EGenerationType : uint8
{
	GT_3D UMETA(DisplayName = "3D"),
	GT_2D UMETA(DisplayName = "2D"),
};