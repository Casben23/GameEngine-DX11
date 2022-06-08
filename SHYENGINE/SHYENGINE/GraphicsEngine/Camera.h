#pragma once
#include "SceneObject.h"
#include "Math/Matrix/Vector.hpp"
#include "Timer.h"
#include "InputHandler.h"
class Camera : public SceneObject
{
	CommonUtilities::Matrix4x4<float> myProjection;

	float myNearPlane = 0.01f;
	float myFarPlane = 1500.0f;

private:

	float mySpeed = 20;
	float myLookSensentivity = 0.01f;

public: 
	bool Init(float aHorizontalFoV, CommonUtilities::Vector2<unsigned int> aResolution, float aNearPlane, float aFarPlane);

	void Update();
	void Move();
	void LookAround();

	FORCEINLINE CommonUtilities::Matrix4x4<float> const& GetProjection() const { return myProjection; }
	FORCEINLINE float GetNearPlane() const { return myNearPlane; }
	FORCEINLINE	float GetFarPlane() const { return myFarPlane; }
};

