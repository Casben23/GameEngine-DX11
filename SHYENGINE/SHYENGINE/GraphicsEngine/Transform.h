#pragma once
#include "Math/Matrix/Matrix4x4.hpp"
#include "Math/Matrix/Vector.hpp"
class Transform
{
public:
	Transform();
	~Transform() = default;

	void SetTransform(Matrix4x4f someTransform);
	void SetRotation(float aPitch, float aYaw, float aRoll);
	void SetPosition(float X, float Y, float Z);
	void SetScale(float X, float Y, float Z);

	Vector3f& GetPosition() { return myPosition; }
	Vector3f& GetRotation() { return myRotation; }
	Vector3f& GetScale() { return myScale; }
	Matrix4x4f& GetMatrix() { return myMatrix; }

	void RebuildMatrix();

private:
	Matrix4x4f myMatrix;

	CommonUtilities::Vector3<float> myRotation;
	CommonUtilities::Vector3<float> myScale = { 1,1,1 };
	CommonUtilities::Vector3<float> myPosition;
};

