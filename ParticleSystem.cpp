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

void ParticleSystem::Draw(ID3D11DeviceContext* pImmediateContext, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
	ConstantBuffer cBuffer = cb;
	for(auto &particle : mParticles)
	{
		// Copy material to shader
		cBuffer.surface.AmbientMtrl = particle->GetAppearance()->GetMaterial().ambient;
		cBuffer.surface.DiffuseMtrl = particle->GetAppearance()->GetMaterial().diffuse;
		cBuffer.surface.SpecularMtrl = particle->GetAppearance()->GetMaterial().specular;

		// Set world matrix
		cBuffer.World = XMMatrixTranspose(particle->GetWorldMatrix());

		//no texture
		cBuffer.HasTexture = 0.0f;

		pImmediateContext->UpdateSubresource(constantBuffer, 0, nullptr, &cBuffer, 0, 0);

		particle->Draw(pImmediateContext);
	}
}

void ParticleSystem::Update(float t)
{
	for (auto &particle : mParticles)
	{
		particle->Update(t);
	}
}

void ParticleSystem::CreateParticles(int num, Geometry geometry, Material material, Vector3D rotation, Vector3D scale, Vector3D color, float mass, float lifeSpan)
{
	for (int i = 0; i < num; i++)
	{
		if (mParticles.size() >= mMaxParticles)
		{
			return;
		}

		Transform* transform = new Transform(Vector3D(0.0f, 0.0f, 0.0f), rotation, scale);

		PhysicsModel* pPhysics = new PhysicsModel(transform);
		pPhysics->SetMass(mass);

		mParticles.push_back(new Particle("Particle", new Appearance(geometry, material), transform, this->mTransform, pPhysics, color, lifeSpan));
	}
}