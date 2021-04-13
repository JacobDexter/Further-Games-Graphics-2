#pragma once
#include "Structures.h"
#include "Appearance.h"
#include <vector>

class TerrainGenerator
{
public:
	static Geometry GenerateTerrainMesh(int row, int col, float quadWidth, float quadHeight, ID3D11Device* device);
private:
	static std::vector<SimpleVertex> GenerateVertices(int row, int col, float quadWidth, float quadHeight);
	static std::vector<WORD> GenerateIndices(int row, int col);
};
