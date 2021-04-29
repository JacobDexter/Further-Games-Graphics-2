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

void GameObject::CollisionAABB(GameObject* object, const float dt) noexcept
{
    // adjust x/z collision scaling for pressure plate
    static float offset = 0.5f;

    // test collision between cube and given object
        //x coll
    if ((mTransform->GetPosition().x - offset <= object->GetTransform()->GetPosition().x + offset &&
        mTransform->GetPosition().x + offset >= object->GetTransform()->GetPosition().x - offset) &&
        //y coll
        (mTransform->GetPosition().y - offset <= object->GetTransform()->GetPosition().y + offset &&
            mTransform->GetPosition().y + offset >= object->GetTransform()->GetPosition().y - offset) &&
        //z coll
        (mTransform->GetPosition().z - offset <= object->GetTransform()->GetPosition().z + offset &&
            mTransform->GetPosition().z + offset >= object->GetTransform()->GetPosition().z - offset)
        )
    {
        CollisionRes(object, dt);
    }
}

void GameObject::CollisionRes(GameObject* object, const float dt) noexcept
{
    float velocityOne = std::max(mPhysicsModel->Magnitude(mPhysicsModel->GetNetForce()), 1.0f);
    float velocityTwo = std::max(object->GetPhysicsModel()->Magnitude(object->GetPhysicsModel()->GetNetForce()), 1.0f);

    float forceMagnitude = (mPhysicsModel->GetMass() * velocityOne + object->GetPhysicsModel()->GetMass() * velocityTwo) / dt;
    Vector3D force;
    force.x = object->GetTransform()->GetPosition().x - mTransform->GetPosition().x;
    force.y = object->GetTransform()->GetPosition().y - mTransform->GetPosition().y;
    force.z = object->GetTransform()->GetPosition().z - mTransform->GetPosition().z;

    force.x = mPhysicsModel->Normalization(force).x * forceMagnitude * 0.015f;
    force.y = mPhysicsModel->Normalization(force).y * forceMagnitude * 0.175f;
    force.z = mPhysicsModel->Normalization(force).z * forceMagnitude * 0.015f;

    Vector3D force2 = {
        -force.x,
        -force.y,
        -force.z,
    };

    mPhysicsModel->AddNetForce(force2);
    object->GetPhysicsModel()->AddNetForce(force);

    OutputDebugStringA(string(mType + " has collided with " + object->GetType() + ".\n").c_str());
}
