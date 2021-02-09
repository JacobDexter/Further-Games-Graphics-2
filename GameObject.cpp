#include "GameObject.h"

GameObject::GameObject(string type, Appearance* appearance, Transform* transform, ParticleModel* particleModel) : _type(type), _appearance(appearance), _transform(transform), _particleModel(particleModel)
{
	_parent = nullptr;
	_world = XMFLOAT4X4();
}

GameObject::~GameObject()
{
	if (_transform) delete _transform; 
	if (_appearance) delete _appearance;
	if (_particleModel) delete _particleModel;
	if (_parent) delete _parent;
}

void GameObject::Update(float t)
{
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_transform->GetScale().x, _transform->GetScale().y, _transform->GetScale().z);
	XMMATRIX rotation = XMMatrixRotationX(_transform->GetRotation().x) * XMMatrixRotationY(_transform->GetRotation().y) * XMMatrixRotationZ(_transform->GetRotation().z);
	XMMATRIX translation = XMMatrixTranslation(_transform->GetPosition().x, _transform->GetPosition().y, _transform->GetPosition().z);

	XMStoreFloat4x4(&_world, scale * rotation * translation);

	//debug
	OutputDebugStringA((_type + " " + to_string(_transform->GetPosition().show_X()) + " " + to_string(_transform->GetPosition().show_Y()) + "\n").c_str());

	_particleModel->Update(t);

	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, XMLoadFloat4x4(&_world) * _parent->GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext* pImmediateContext)
{
	_appearance->Draw(pImmediateContext);
}
