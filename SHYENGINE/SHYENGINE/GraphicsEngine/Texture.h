#pragma once
#include <iostream>
#include "DX11.h"
#include <wrl.h>
class Texture
{
	friend class TextureAssetHandler;
	
protected:
	std::wstring myName;
	
	ComPtr<struct ID3D11Resource> myTexture;
	ComPtr<struct ID3D11ShaderResourceView> mySRV;

public:
	virtual ~Texture();

	void SetAsResource(unsigned int aSlot);
	
};

