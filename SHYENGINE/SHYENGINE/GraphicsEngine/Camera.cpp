#define _USE_MATH_DEFINES

#include "GraphicsEngine.pch.h"
#include "Camera.h"
#include <cmath>
#include <iostream>
bool Camera::Init(float aHorizontalFoV, CommonUtilities::Vector2<unsigned int> aResolution, float aNearPlane, float aFarPlane)
{
	assert(aNearPlane < aFarPlane);
	assert(aNearPlane >= 0.000005f);

	myNearPlane = aNearPlane;
	myFarPlane = aFarPlane;

	const float hFoVRad = aHorizontalFoV * (3.144569087245086 / 180);

	const float vFoVRad = 2 * std::atan(std::tan(hFoVRad / 2) * (static_cast<float>(aResolution.y) / static_cast<float>(aResolution.x)));

	const float myXScale = 1 / std::tanf(hFoVRad * 0.5f);
	const float myYScale = 1 / std::tanf(vFoVRad * 0.5f);
	const float Q = myFarPlane / (myFarPlane - myNearPlane);

	myProjection(1, 1) = myXScale;
	myProjection(2, 2) = myYScale;
	myProjection(3, 3) = Q;
	myProjection(3, 4) = 1.0f / Q;
	myProjection(4, 3) = -Q * myNearPlane;
	myProjection(4, 4) = 0.0f;

	return true;
}

void Camera::Update()
{
	Move();
	LookAround();
}

void Camera::Move()
{
	if (InputHandler::IsKeyPressed(eKeyCode::W))
	{
		Vector3f rotationZ = { myTransform(3,1),myTransform(3,2), myTransform(3,3) };
		myPosition += rotationZ * mySpeed * 0.1f;
		RebuildMatrix();
	}
	if (InputHandler::IsKeyPressed(eKeyCode::S))
	{
		Vector3f rotationZ = { -myTransform(3,1),-myTransform(3,2),-myTransform(3,3) };
		myPosition += rotationZ * mySpeed * 0.1f;
		RebuildMatrix();
	}
	if (InputHandler::IsKeyPressed(eKeyCode::A))
	{
		Vector3f rotationZ = { -myTransform(1,1),-myTransform(1,2),-myTransform(1,3) };
		myPosition += rotationZ * mySpeed * 0.1f;
		RebuildMatrix();
	}
	if (InputHandler::IsKeyPressed(eKeyCode::D))
	{
		Vector3f rotationZ = { myTransform(1,1),myTransform(1,2),myTransform(1,3)};
		myPosition += rotationZ * mySpeed * 0.1f;
		RebuildMatrix();
	}
	if (InputHandler::IsKeyPressed(VK_SPACE))
	{
		Vector3f rotationZ = { myTransform(2,1),myTransform(2,2),myTransform(2,3) };
		myPosition += rotationZ * mySpeed * 0.1f;
		RebuildMatrix();
	}
	if (InputHandler::IsKeyPressed(VK_CONTROL))
	{
		Vector3f rotationZ = { -myTransform(2,1),-myTransform(2,2),-myTransform(2,3) };
		myPosition += rotationZ * mySpeed * 0.1f;
		RebuildMatrix();
	}

	if (InputHandler::IsKeyPressed(VK_SHIFT))
	{
		mySpeed = 20;
	}
	else
	{
		mySpeed = 10;
	}
}

void Camera::LookAround()
{
	if (InputHandler::IsKeyPressed(eKeyCode::RMB))
	{
		Vector3f mouseDelta = { static_cast<float>(InputHandler::GetDeltaMousePosition().y), static_cast<float>(InputHandler::GetDeltaMousePosition().x), 0 };
		myRotation += mouseDelta * myLookSensentivity * 0.1f;
		RebuildMatrix();
	}
}
