#pragma once
#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include "Particle.h"
#include "GameObject.h"
#include "Structures.h"

using namespace std;

class ParticleSystem
{
public:
	ParticleSystem(Transform* transform, GameObject* parent, int maxParticles);
	ParticleSystem(Transform* transform, int maxParticles);
	~ParticleSystem();

	void Draw(ID3D11DeviceContext* pImmediateContext, ConstantBuffer cb, ID3D11Buffer* constantBuffer);
	void Update(float t);

	void CreateParticles(int num, Geometry geometry, Material material, Vector3D rotation, Vector3D scale, Vector3D color, float mass, float lifeSpan);

	//get/set
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&mWorld); }
	XMFLOAT4X4 GetWorldFloat4X4() const { return mWorld; }

	Transform* GetTransform() const { return mTransform; }

	vector<Particle*> GetParticles() const { return mParticles;  }
	GameObject* GetParent() const { return mParent;  }
private:
	//components
	GameObject* mParent;
	Transform* mTransform;
	vector<Particle*> mParticles;

	//properties
	XMFLOAT4X4 mWorld = XMFLOAT4X4();
	int mMaxParticles;
};

#endif