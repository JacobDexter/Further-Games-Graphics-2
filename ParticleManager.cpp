#include "ParticleManager.h"

ParticleManager::ParticleManager()
{

}

ParticleManager::~ParticleManager()
{

}

void ParticleManager::CreateParticleSystem(Transform* transform, GameObject* parent, int maxParticles)
{
	mParticleSystems.push_back(new ParticleSystem(transform, parent, maxParticles));
}

void ParticleManager::CreateParticleSystem(Transform* transform, int maxParticles)
{
	mParticleSystems.push_back(new ParticleSystem(transform, maxParticles));
}

void ParticleManager::RemoveParticleSystem()
{

}

void ParticleManager::EnableParticleSystem()
{

}

void ParticleManager::DisableParticleSystem()
{

}
