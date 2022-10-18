#include "GraphicsEngine.pch.h"
#include "Light.h"

void Light::Init(Vector4f aColor, float anIntensity)
{
	myLightBufferData.myColor = aColor;
	myLightBufferData.myIntensity = anIntensity;
	myLightBufferData.myFarPlane = 3000;
	myLightBufferData.myNearPlane = 0.01f;
}
