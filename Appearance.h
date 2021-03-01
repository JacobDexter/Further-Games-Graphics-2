#pragma once
#include <directxmath.h>
#include <d3d11_1.h>

using namespace DirectX;

struct Geometry
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int numberOfIndices;

	UINT vertexBufferStride;
	UINT vertexBufferOffset;
};

struct Material
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
	float specularPower;
};

class Appearance
{
public:
	Appearance(Geometry geometry, Material material);
	~Appearance();

	void Draw(ID3D11DeviceContext* pImmediateContext);

	Geometry GetGeometryData() const { return mGeometry; }
	Material GetMaterial() const { return mMaterial; }

	//texturing
	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { mTextureRV = textureRV; }
	ID3D11ShaderResourceView* GetTextureRV() const { return mTextureRV; }
	bool HasTexture() const { return mTextureRV ? true : false; }
private:
	Geometry mGeometry;
	Material mMaterial;

	ID3D11ShaderResourceView* mTextureRV;
};