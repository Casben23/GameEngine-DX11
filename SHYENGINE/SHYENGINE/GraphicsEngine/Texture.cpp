#include "GraphicsEngine.pch.h"
#include "Texture.h"

Texture::~Texture()
{
	myTexture.Reset();
	mySRV.Reset();
}

void Texture::SetAsResource(unsigned int aSlot)
{	
	DX11::myContext->PSSetShaderResources(aSlot, 1, mySRV.GetAddressOf());
}
