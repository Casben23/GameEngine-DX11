#include "GraphicsEngine.pch.h"
#include "Material.h"

Material::Material()
{
}

void Material::Init(const std::wstring aName, const Vector3f& aAlbedo)
{
	myName = aName;
	myAlbedo = aAlbedo;
}
