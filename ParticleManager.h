#pragma once
#include "ParticleSystem.h"

class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();

	void CreateParticleSystem(ParticleSystem* pSystem);
	void DeleteParticleSystem(ParticleSystem* pSystem);
};