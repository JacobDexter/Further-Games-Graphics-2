#include "Particle.h"

Particle::Particle(string type, Appearance* appearance, Transform* transform, Transform* systemTransform, PhysicsModel* physicsModel, Vector3D color, float lifeSpan) : GameObject(type, appearance, transform, physicsModel), mParentTransform(systemTransform), mColor(color), mLifeSpan(lifeSpan)
{
	mTransform->SetPosition(mParentTransform->GetPosition());
	GameObject::SetIsStatic(false);
	mCurrentLife = Timer();
	mCurrentLife.Start();
}

Particle::~Particle()
{

}

void Particle::Draw(ID3D11DeviceContext* pImmediateContext)
{
	if (!mIsDisabled)
	{
		GameObject::Draw(pImmediateContext);
	}
}

void Particle::Update(float t)
{
	if (!mIsDisabled)
	{
		mPhysicsModel->SetVelocity(Vector3D(0.0f, 50.0f, 0.0f));
		GameObject::Update(t);
		
		if (mCurrentLife.GetMilliSecondsElapsed() > mLifeSpan)
		{
			mTransform->SetPosition(mParentTransform->GetPosition());
			mCurrentLife.Restart();
		}
	}
}

void Particle::ResetParticlePosition()
{
	mTransform->SetPosition(mParentTransform->GetPosition());
}
