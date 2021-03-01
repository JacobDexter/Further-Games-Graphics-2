#pragma once
#include <DirectXMath.h>
#include "Vector3D.h"
#include "Transform.h"
#include "Quaternion.h"

class PhysicsModel
{
public:
	PhysicsModel(Transform* transform);
	~PhysicsModel();

	//get/set forces
	Vector3D GetVelocity() const { return mVelocity; }
	void SetVelocity(Vector3D velocity) { mVelocity = velocity; }

	Vector3D GetAcceleration() const { return mAcceleration; }
	void SetAcceleration(Vector3D acceleration) { mAcceleration = acceleration; }

	Vector3D GetDrag() const { return mDrag; }
	void SetDrag(Vector3D drag) { mDrag = drag; }

	//set/get object properties
	float GetMass() const { return mMass; }
	void SetMass(float mass) { mMass = mass; }

	float GetWeight() const { return mWeight; }

	Quaternion GetQuaternion() const { return mQuaternion; }
	void SetQuaternion(Quaternion quaternion) { mQuaternion = quaternion; }

	//add forces
	void AddNetForce(Vector3D force) { mNetForce += force; }
	void AddAcceleration(Vector3D acceleration) { mAcceleration += acceleration; }
	void AddVelocity(Vector3D velocity) { mVelocity += velocity; }
	void AddDrag(Vector3D drag) { mDrag += drag; }

	//reset forces
	void ResetNetForce() { mNetForce = { 0.0f, 0.0f, 0.0f }; }
	void ResetVelocity() { mVelocity = { 0.0f, 0.0f, 0.0f }; }
	void ResetAcceleration() { mAcceleration = { 0.0f, 0.0f, 0.0f }; }
	void ResetDrag() { mDrag = { 0.0f, 0.0f, 0.0f }; }

	//functions for updating forces and object position
	virtual void Update(const float deltaTime);
	void AddWeight();
	void CalculateAcceleration();
	void CalculateVelocity(const float deltaTime);
	void AddFriction(const float deltaTime);

	void AddDrag();
	void LaminarDrag();
	void TurbulentDrag();

	void CalculatePosition(const float deltaTime);
	void AddGravity();
private:
	//constants
	float mGravity = 9.81f;
	float mDragFactor = 0.75f;

	//local property variables
	Transform* mTransform;
	Quaternion mQuaternion;
	Vector3D mPosition;
	Vector3D mNetForce;
	Vector3D mVelocity;
	Vector3D mAcceleration;
	Vector3D mDrag;
	float mMass;
	float mWeight;
	bool mUseLaminar;
};