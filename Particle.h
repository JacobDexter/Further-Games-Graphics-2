#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include <DirectXMath.h>
#include "Transform.h"
#include "PhysicsModel.h"

using namespace DirectX;

class Particle
{
public:
	Particle(Transform* systemTransform, Transform* transform, PhysicsModel* physicsModel, Vector3D color, float lifeSpan);
	~Particle();

	void Draw();
	void Update(float t);

	void EnableParticle() { isDisabled = false; }
	void DisableParticle() { isDisabled = true; }
	void ResetParticlePosition();

	//get/set
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&mWorld); }
	XMFLOAT4X4 GetWorldFloat4X4() const { return mWorld; }

	Transform* GetTransform() const { return mTransform; }
	PhysicsModel* GetPhysicsModel() const { return mPhysicsModel; }
private:
	//components
	Transform* mTransform;
	Transform* mParentTransform;
	PhysicsModel* mPhysicsModel;

	//properties
	XMFLOAT4X4 mWorld = XMFLOAT4X4();
	Vector3D mColor;
	float mlifeSpan;
	bool isDisabled = false;
};

#endif