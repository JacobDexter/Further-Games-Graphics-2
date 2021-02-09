#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "Debugger.h"
#include "Vector3D.h"
#include "Transform.h"
#include "Appearance.h"
#include "ParticleModel.h"

using namespace DirectX;
using namespace std;

class GameObject
{
public:
	GameObject(string type, Appearance* appearance, Transform* transform, ParticleModel* particleModel);
	~GameObject();

	void Draw(ID3D11DeviceContext* pImmediateContext);

	string GetType() const { return _type; }

	Transform* GetTransform() const { return _transform;  }
	Appearance* GetAppearance() const { return _appearance;  }
	ParticleModel* GetParticleModel() const { return _particleModel;  }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }
	XMFLOAT4X4 GetWorldFloat4X4() const { return _world; }

	void SetParent(GameObject* parent) { _parent = parent; }

	void Update(float t);

private:
	XMFLOAT4X4 _world;

	Transform* _transform;
	Appearance* _appearance;
	ParticleModel* _particleModel;

	string _type;
	GameObject* _parent;
};

