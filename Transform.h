#pragma once
#include "Vector3D.h"

class Transform
{
public:
	Transform(Vector3D position, Vector3D rotation, Vector3D scale) : _position(position), _rotation(rotation), _scale(scale) { }

	// set/get
	void SetPosition(Vector3D position) { _position = position; }
	void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }

	Vector3D GetPosition() const { return _position; }

	void SetScale(Vector3D scale) { _scale = scale; }
	void SetScale(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }

	Vector3D GetScale() const { return _scale; }

	void SetRotation(Vector3D rotation) { _rotation = rotation; }
	void SetRotation(float x, float y, float z) { _rotation.x = x; _rotation.y = y; _rotation.z = z; }

	Vector3D GetRotation() const { return _rotation; }
private:
	Vector3D _position;
	Vector3D _rotation;
	Vector3D _scale;
};