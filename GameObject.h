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

	virtual void Draw(ID3D11DeviceContext* pImmediateContext);
	virtual void Update(float t);

	string GetType() const { return mType; }

	Transform* GetTransform() const { return mTransform;  }
	Appearance* GetAppearance() const { return mAppearance;  }
	PhysicsModel* GetPhysicsModel() const { return mPhysicsModel;  }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&mWorld); }
	XMFLOAT4X4 GetWorldFloat4X4() const { return mWorld; }

	Quaternion GetQuaternion() const { return mQuaternion; }
	void SetQuaternion(Quaternion quaternion) { mQuaternion = quaternion; }

	bool GetIsStatic() const { return mIsStatic; }
	void SetIsStatic(bool isStatic) { mIsStatic = isStatic; }

	void SetParent(GameObject* parent) { mParent = parent; }

protected:
	XMFLOAT4X4 mWorld = XMFLOAT4X4();
	Quaternion mQuaternion;

	//componenets
	Transform* mTransform;
	Appearance* mAppearance;
	PhysicsModel* mPhysicsModel;
	GameObject* mParent;

	string mType;

	bool mIsStatic = false;
};

