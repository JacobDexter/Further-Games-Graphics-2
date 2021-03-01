#include "GameObject.h"

GameObject::GameObject(string type, Appearance* appearance, Transform* transform, PhysicsModel* physicsModel) : _type(type), _appearance(appearance), _transform(transform), _physicsModel(physicsModel)
{
	_parent = nullptr;
}

GameObject::~GameObject()
{
	if (_transform) delete _transform; 
	if (_appearance) delete _appearance;
	if (_physicsModel) delete _physicsModel;
	if (_parent) delete _parent;
}

void GameObject::Update(float t)
{
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_transform->GetScale().x, _transform->GetScale().y, _transform->GetScale().z);
	XMMATRIX rotation = XMMatrixRotationX(_transform->GetRotation().x) * XMMatrixRotationY(_transform->GetRotation().y) * XMMatrixRotationZ(_transform->GetRotation().z);
	XMMATRIX translation = XMMatrixTranslation(_transform->GetPosition().x, _transform->GetPosition().y, _transform->GetPosition().z);

	XMStoreFloat4x4(&_world, scale * rotation * translation);
	
	if (!_isStatic)
	{
		_physicsModel->Update(1.0f / t);
	}

	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, XMLoadFloat4x4(&_world) * _parent->GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext* pImmediateContext)
{
	_appearance->Draw(pImmediateContext);
}
