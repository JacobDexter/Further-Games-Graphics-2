#pragma once
#include "Vector3D.h"

class Transform
{
public:
	Transform(Vector3D position, Vector3D rotation, Vector3D scale) : mPosition(position), mRotation(rotation), mScale(scale) { }

	// set/get
	void SetPosition(Vector3D position) { mPosition = position; }
	void SetPosition(float x, float y, float z) { mPosition.x = x; mPosition.y = y; mPosition.z = z; }

	Vector3D GetPosition() const { return mPosition; }

	void SetScale(Vector3D scale) { mScale = scale; }
	void SetScale(float x, float y, float z) { mScale.x = x; mScale.y = y; mScale.z = z; }

	Vector3D GetScale() const { return mScale; }

	void SetRotation(Vector3D rotation) { mRotation = rotation; }
	void SetRotation(float x, float y, float z) { mRotation.x = x; mRotation.y = y; mRotation.z = z; }

	Vector3D GetRotation() const { return mRotation; }
private:
	Vector3D mPosition;
	Vector3D mRotation;
	Vector3D mScale;
};