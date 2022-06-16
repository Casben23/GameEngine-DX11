#include "GraphicsEngine.pch.h"
#include "Light.h"

void Light::Init(Vector4f aColor, float anIntensity)
{
	myLightBufferData.myColor = aColor;
	myLightBufferData.myIntensity = anIntensity;
}
