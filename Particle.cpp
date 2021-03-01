#include "Particle.h"

Particle::Particle(Transform* systemTransform, Transform* transform, PhysicsModel* physicsModel, Vector3D color, float lifeSpan) : mParentTransform(systemTransform), mPhysicsModel(physicsModel), mTransform(transform), mColor(color)
{
	mTransform->SetPosition(mParentTransform->GetPosition());
}

Particle::~Particle()
{

}

void Particle::Draw()
{

}

void Particle::Update(float t)
{

}

void Particle::ResetParticlePosition()
{
	mTransform->SetPosition(mParentTransform->GetPosition());
}
