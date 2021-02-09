#include "ParticleModel.h"

ParticleModel::ParticleModel(Transform* transform, bool useConstVelocity, Vector3D iniVelocity, bool useConstAcceleration, Vector3D iniAcceleration, Vector3D mass, Vector3D netForce) : _transform(transform), _velocity(iniVelocity), _acceleration(iniAcceleration), _mass(mass), _netForce(netForce)
{
	_usingVelocity = useConstVelocity;
	_usingAcceleration = useConstAcceleration;
}

ParticleModel::~ParticleModel()
{
	
}

void ParticleModel::Update(float t)
{
	if (_usingVelocity)
	{
		MoveConstVelocity(t);
	}

	if (_usingAcceleration)
	{
		MoveConstAcceleration(t);
	}
}

void ParticleModel::MoveConstVelocity(const float deltaTime)
{
	_position = _transform->GetPosition();

	// update world position of object by adding displacement (i.e.  velocity x time step) to  previous position
	_position.x = _position.x + _velocity.x * deltaTime;
	_position.y = _position.y + _velocity.y * deltaTime;
	_position.z = _position.z + _velocity.z * deltaTime;
	_transform->SetPosition(_position);
}

void ParticleModel::MoveConstAcceleration(const float deltaTime)
{
	_position = _transform->GetPosition();

	// update world position of object by adding displacement to previously calculated position  
	_position.x = _position.x + _velocity.x * deltaTime + 0.5f * _acceleration.x * deltaTime * deltaTime;
	_position.y = _position.y + _velocity.y * deltaTime + 0.5f * _acceleration.y * deltaTime * deltaTime;
	_position.z = _position.z + _velocity.z * deltaTime + 0.5f * _acceleration.z * deltaTime * deltaTime;
	_transform->SetPosition(_position);

	// update velocity of object by adding change relative to previously calculated velocity  
	_velocity.x = _velocity.x + _acceleration.x * deltaTime;
	_velocity.y = _velocity.y + _acceleration.y * deltaTime;
	_velocity.z = _velocity.z + _acceleration.z * deltaTime;
}

void ParticleModel::UpdateNetForce()
{

}

void ParticleModel::UpdateAcceleration()
{

}
