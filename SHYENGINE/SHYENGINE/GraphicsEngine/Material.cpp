#include "GraphicsEngine.pch.h"
#include "Material.h"

Material::Material()
{
}

void Material::Init(const std::wstring aName, const Vector3f& aAlbedo)
{
	myName = aName;
	myMaterialData.myAlbedo = aAlbedo;
}

void Material::SetAlbedoTexture(std::shared_ptr<Texture> aTexture)
{
	myTextures[0] = aTexture;
}

void Material::SetNormalTexture(std::shared_ptr<Texture> aTexture)
{
	myTextures[1] = aTexture;
}

void Material::SetMaterialTexture(std::shared_ptr<Texture> aTexture)
{
	myTextures[2] = aTexture;
}

void Material::SetAsResource(ComPtr<ID3D11Resource> aMaterialBuffer)
{
	D3D11_MAPPED_SUBRESOURCE bufferData;
	ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));

	const HRESULT result = DX11::myContext->Map(
		aMaterialBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&bufferData);

	if (FAILED(result))
	{
		std::cout << "Set Material Resource Did Not Work!" << std::endl;
	}

	memcpy_s(bufferData.pData, sizeof(MaterialData), &myMaterialData, sizeof(MaterialData));

	DX11::myContext->Unmap(aMaterialBuffer.Get(), 0);

	if (myTextures[MaterialTextureChannel::Albedo])
		myTextures[MaterialTextureChannel::Albedo]->SetAsResource(0);
	if (myTextures[MaterialTextureChannel::Normal])
		myTextures[MaterialTextureChannel::Normal]->SetAsResource(1);
	if (myTextures[MaterialTextureChannel::Material])
		myTextures[MaterialTextureChannel::Material]->SetAsResource(2);
}
