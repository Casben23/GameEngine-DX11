#include "GraphicsEngine.pch.h"
#include "Transform.h"
Transform::Transform()
{
	
}
void Transform::SetTransform(Matrix4x4f someTransform)
{
	myMatrix = someTransform;
}

void Transform::SetRotation(float aPitch, float aYaw, float aRoll)
{
	myRotation = { aPitch, aYaw, aRoll };
	RebuildMatrix();
}

void Transform::SetPosition(float X, float Y, float Z)
{
	myPosition = { X,Y,Z };
	RebuildMatrix();
}

void Transform::SetScale(float X, float Y, float Z)
{
	myScale = { X,Y,Z };
	RebuildMatrix();
}

void Transform::RebuildMatrix()
{
	Matrix4x4f matrix;

	matrix(1, 1) = myScale.x;
	matrix(2, 2) = myScale.y;
	matrix(3, 3) = myScale.z;

	matrix *= Matrix4x4f::CreateRotationAroundX(myRotation.x);
	matrix *= Matrix4x4f::CreateRotationAroundY(myRotation.y);
	matrix *= Matrix4x4f::CreateRotationAroundZ(myRotation.z);

	matrix(4, 1) = myPosition.x;
	matrix(4, 2) = myPosition.y;
	matrix(4, 3) = myPosition.z;

	myMatrix = matrix;
}