#pragma once
#include "Math/Matrix/Matrix4x4.hpp"
#include "Math/Matrix/Vector.hpp"
class SceneObject
{
protected:
	Matrix4x4f myTransform;

	CommonUtilities::Vector3<float> myRotation;
	CommonUtilities::Vector3<float> myScale = { 1,1,1 };
	CommonUtilities::Vector3<float> myPosition;

public:
	SceneObject() = default;
	virtual ~SceneObject() = default;

	void SetTransform(Matrix4x4f someTransform);
	void SetRotation(float aPitch, float aYaw, float aRoll);
	void SetLocation(float X, float Y, float Z);
	void SetScale(float X, float Y, float Z);

	void RebuildMatrix();

	FORCEINLINE CommonUtilities::Matrix4x4<float> const& GetTransform() const { return myTransform; }
};

