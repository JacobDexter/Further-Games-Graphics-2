#pragma once
#include <DirectXMath.h>
#include "Vector3D.h"
#include "Transform.h"

using namespace DirectX;

class ParticleModel
{
public:
	ParticleModel(Transform* transform, bool useConstVelocity, Vector3D iniVelocity, bool useConstAcceleration, Vector3D iniAcceleration, Vector3D mass, Vector3D netForce);
	~ParticleModel();

	void Update(float t);

	void MoveConstVelocity(const float deltaTime);
	void MoveConstAcceleration(const float deltaTime);

	void UpdateNetForce();
	void UpdateAcceleration();

	void SetVelocity(Vector3D velocity) { _velocity = velocity;  }
	Vector3D GetVelocity() const { return _velocity; }

	void SetAcceleration(Vector3D acceleration) { _acceleration = acceleration; }
	Vector3D GetAcceleration() const { return _acceleration; }

	void SetNetForce(Vector3D netForce) { _netForce = netForce; }
	Vector3D GetNetForce() const { return _netForce; }

	void SetMass(Vector3D mass) { _mass = mass; }
	Vector3D GetMass() const { return _mass; }

	void SetUsingVelocity(bool velocity) { _usingVelocity = velocity; }
	void SetUsingAcceleration(bool acceleration) { _usingAcceleration = acceleration; }

private:
	//using
	bool _usingVelocity, _usingAcceleration;

	//position
	Transform* _transform;

	//movement
	Vector3D _position;
	Vector3D _velocity;
	Vector3D _acceleration;
	Vector3D _netForce;

	//object properties
	Vector3D _mass;
};