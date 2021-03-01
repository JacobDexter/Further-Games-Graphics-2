#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Transform* transform, GameObject* parent, int maxParticles) : mTransform(transform), mParent(parent), mMaxParticles(maxParticles)
{
	
}

ParticleSystem::ParticleSystem(Transform* transform, int maxParticles) : mTransform(transform), mMaxParticles(maxParticles)
{
	mParent = nullptr;
}

ParticleSystem::~ParticleSystem()
{
	
}

void ParticleSystem::Draw()
{
	for(auto &particle : mParticles)
	{
		particle->Draw();
	}
}

void ParticleSystem::Update(float t)
{
	for (auto &particle : mParticles)
	{
		particle->Update(t);
	}
}

void ParticleSystem::CreateParticles(int num, Vector3D position, Vector3D rotation, Vector3D scale, Vector3D color, float mass, float lifeSpan)
{
	for (int i = 0; i < num; i++)
	{
		if (mParticles.size() >= mMaxParticles)
		{
			return;
		}

		Transform* pTransform = new Transform(position, rotation, scale);
		PhysicsModel* pPhysics = new PhysicsModel(pTransform);
		pPhysics->SetMass(mass);
		mParticles.push_back(new Particle(mTransform, pTransform, pPhysics, color, lifeSpan));
	}
}
