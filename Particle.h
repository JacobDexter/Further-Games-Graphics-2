#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include "GameObject.h"
#include "Timer.h"

using namespace DirectX;

class Particle : public GameObject
{
public:
	Particle(string type, Appearance* appearance, Transform* transform, Transform* systemTransform, PhysicsModel* physicsModel, Vector3D color, float lifeSpan);
	~Particle();

	void Draw(ID3D11DeviceContext* pImmediateContext) override;
	void Update(float t) override;

	void MovementForces(); //temp

	void EnableParticle() { mIsDisabled = false; }
	void DisableParticle() { mIsDisabled = true; }
	void ResetParticlePosition();

private:
	//components
	Transform* mParentTransform;

	//properties
	Vector3D mColor;
	float mLifeSpan;
	Timer mCurrentLife;
	bool mIsDisabled = false;
};

#endif