#include "GraphicsEngine.pch.h"
#include "GBuffer.h"
#include "DX11.h"
void GBuffer::SetAsTarget() const 
{
}

void GBuffer::ClearTarget() const 
{
}

void GBuffer::SetAsResource(unsigned int aStartSlot) const
{
	ID3D11ShaderResourceView* mySRVList[GBufferTexture::GB_COUNT];
	for (unsigned t = 0; t < mySRVs.size(); t++)
		mySRVList[t] = mySRVs[t].Get();
	DX11::myContext->PSSetShaderResources(aStartSlot,
		GBufferTexture::GB_COUNT,
		&mySRVList[0]);
}

void GBuffer::ClearResource(unsigned int aStartSlot) const 
{
}

void GBuffer::Clear() const
{
}
