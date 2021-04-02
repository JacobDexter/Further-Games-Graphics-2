#include "GameObject.h"

GameObject::GameObject(string type, Appearance* appearance, Transform* transform, PhysicsModel* physicsModel) : mType(type), mAppearance(appearance), mTransform(transform), mPhysicsModel(physicsModel)
{
	mParent = nullptr;
}

GameObject::~GameObject()
{
	if (mTransform) delete mTransform; 
	if (mAppearance) delete mAppearance;
	if (mPhysicsModel) delete mPhysicsModel;
	if (mParent) delete mParent;
}

void GameObject::Update(float t)
{
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(mTransform->GetScale().x, mTransform->GetScale().y, mTransform->GetScale().z);
	XMMATRIX rotation = XMMatrixRotationX(mTransform->GetRotation().x) * XMMatrixRotationY(mTransform->GetRotation().y) * XMMatrixRotationZ(mTransform->GetRotation().z);
	XMMATRIX translation = XMMatrixTranslation(mTransform->GetPosition().x, mTransform->GetPosition().y, mTransform->GetPosition().z);

	XMStoreFloat4x4(&mWorld, scale * rotation * translation);

	if (!mIsStatic)
	{
		mPhysicsModel->Update(1.0f / t);
	}

	if (mType == "Particle")
	{
		OutputDebugStringA((to_string(mTransform->GetPosition().x) + " - " + to_string(mTransform->GetPosition().y) + " - " + to_string(mTransform->GetPosition().z) + "\n").c_str());
	}

	if (mParent != nullptr)
	{
		XMStoreFloat4x4(&mWorld, XMLoadFloat4x4(&mWorld) * mParent->GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext* pImmediateContext)
{
	mAppearance->Draw(pImmediateContext);
}
