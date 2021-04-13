#include "TerrainGenerator.h"

Geometry TerrainGenerator::GenerateTerrainMesh(int row, int col, float quadWidth, float quadHeight, ID3D11Device* device)
{
	//
	//output
	//
	Geometry geometry;

	//
	//generate vertices and indices
	//
	std::vector<SimpleVertex> vertices = GenerateVertices(row, col, quadWidth, quadHeight);
	std::vector<WORD> indices = GenerateIndices(row, col);

	//
	//vector to array for buffers
	//
	SimpleVertex* vertexArray = new SimpleVertex[vertices.size()];
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		vertexArray[i] = vertices[i];
	}

	WORD* indexArray = new WORD[indices.size()];
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		indexArray[i] = indices[i];
	}

	//
	//setup vertex buffers
	//
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * vertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertexArray;

	device->CreateBuffer(&bd, &InitData, &geometry.vertexBuffer);

	geometry.vertexBufferOffset = 0;
	geometry.vertexBufferStride = sizeof(SimpleVertex);

	//
	//setup index buffers
	//
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indices.size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indexArray;
	device->CreateBuffer(&bd, &InitData, &geometry.indexBuffer);

	geometry.numberOfIndices = indices.size();

	return geometry;
}

std::vector<SimpleVertex> TerrainGenerator::GenerateVertices(int row, int col, float quadWidth, float quadHeight)
{
	std::vector<SimpleVertex> vertices;

	float w = col * quadWidth;
	float d = row * quadHeight;

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			SimpleVertex vertex {};
			vertex.Pos = XMFLOAT3(-0.5f * w + c * quadWidth, 0.0f, 0.5f * d - r * quadHeight);
			vertex.Normal = XMFLOAT3(-0.5f * w + c * quadWidth, 0.0f, 0.5f * d - r * quadHeight);
			vertex.TexC = XMFLOAT2((1.0f / row) * (r + 1), (1.0f / col) * (c + 1));

			vertices.push_back(vertex);
		}
	}

	return vertices;
}

std::vector<WORD> TerrainGenerator::GenerateIndices(int row, int col)
{
	std::vector<WORD> indices;

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			//ABC
			indices.push_back(r * col + c);
			indices.push_back(r * col + c + 1);
			indices.push_back((r + 1) * col + c);

			//CBD
			indices.push_back((r + 1) * col + c);
			indices.push_back(r * col + c + 1);
			indices.push_back((r + 1) * col + c + 1);
		}
	}

	return indices;
}
