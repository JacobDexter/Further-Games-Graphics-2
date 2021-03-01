#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "Debugger.h"
#include "Vector3D.h"
#include "Transform.h"
#include "Appearance.h"
#include "PhysicsModel.h"

class GameObject
{
public:
	GameObject(string type, Appearance* appearance, Transform* transform, PhysicsModel* physicsModel);
	~GameObject();

	void Draw(ID3D11DeviceContext* pImmediateContext);

	string GetType() const { return _type; }

	Transform* GetTransform() const { return _transform;  }
	Appearance* GetAppearance() const { return _appearance;  }
	PhysicsModel* GetPhysicsModel() const { return _physicsModel;  }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }
	XMFLOAT4X4 GetWorldFloat4X4() const { return _world; }

	Quaternion GetQuaternion() const { return mQuaternion; }
	void SetQuaternion(Quaternion quaternion) { mQuaternion = quaternion; }

	bool GetIsStatic() const { return _isStatic; }
	void SetIsStatic(bool isStatic) { _isStatic = isStatic; }

	void SetParent(GameObject* parent) { _parent = parent; }

	void Update(float t);

private:
	XMFLOAT4X4 _world = XMFLOAT4X4();
	Quaternion mQuaternion;

	//componenets
	Transform* _transform;
	Appearance* _appearance;
	PhysicsModel* _physicsModel;
	GameObject* _parent;

	string _type;

	bool _isStatic;
};

