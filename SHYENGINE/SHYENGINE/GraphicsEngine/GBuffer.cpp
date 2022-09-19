#include "GraphicsEngine.pch.h"
#include "GBuffer.h"

GBuffer::GBuffer(float aWidth, float aHeight)
{
	ComPtr<ID3D11Texture2D> bufferTexture;
	D3D11_TEXTURE2D_DESC  bufferDesc = { 0 };
	 bufferDesc.Width = aWidth;
	 bufferDesc.Height = aHeight;
	 bufferDesc.ArraySize = 1;
	 bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	 bufferDesc.SampleDesc.Count = 1;
	 bufferDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	DX11::myDevice->CreateTexture2D(& bufferDesc, nullptr, bufferTexture.GetAddressOf());
	DX11::myDevice->CreateRenderTargetView(bufferTexture.Get(), nullptr, myRTVs[GBufferTexture::GB_ALBEDO].GetAddressOf());
	DX11::myDevice->CreateShaderResourceView(bufferTexture.Get(), nullptr, mySRVs[GBufferTexture::GB_ALBEDO].GetAddressOf());

	bufferDesc.Format = DXGI_FORMAT_R16G16B16A16_SNORM;

	DX11::myDevice->CreateTexture2D(&bufferDesc, nullptr, &bufferTexture);
	DX11::myDevice->CreateRenderTargetView(bufferTexture.Get(), nullptr, myRTVs[GBufferTexture::GB_NORMAL].GetAddressOf());
	DX11::myDevice->CreateShaderResourceView(bufferTexture.Get(), nullptr, mySRVs[GBufferTexture::GB_NORMAL].GetAddressOf());

	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	DX11::myDevice->CreateTexture2D(&bufferDesc, nullptr, &bufferTexture);
	DX11::myDevice->CreateRenderTargetView(bufferTexture.Get(), nullptr, myRTVs[GBufferTexture::GB_MATERIAL].GetAddressOf());
	DX11::myDevice->CreateShaderResourceView(bufferTexture.Get(), nullptr, mySRVs[GBufferTexture::GB_MATERIAL].GetAddressOf());

	bufferDesc.Format = DXGI_FORMAT_R16G16B16A16_SNORM;

	DX11::myDevice->CreateTexture2D(&bufferDesc, nullptr, &bufferTexture);
	DX11::myDevice->CreateRenderTargetView(bufferTexture.Get(), nullptr, myRTVs[GBufferTexture::GB_VERTEXNORMAL].GetAddressOf());
	DX11::myDevice->CreateShaderResourceView(bufferTexture.Get(), nullptr, mySRVs[GBufferTexture::GB_VERTEXNORMAL].GetAddressOf());

	bufferDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	DX11::myDevice->CreateTexture2D(&bufferDesc, nullptr, &bufferTexture);
	DX11::myDevice->CreateRenderTargetView(bufferTexture.Get(), nullptr, myRTVs[GBufferTexture::GB_POSITION].GetAddressOf());
	DX11::myDevice->CreateShaderResourceView(bufferTexture.Get(), nullptr, mySRVs[GBufferTexture::GB_POSITION].GetAddressOf());

	bufferDesc.Format = DXGI_FORMAT_R8_UNORM;

	DX11::myDevice->CreateTexture2D(&bufferDesc, nullptr, &bufferTexture);
	DX11::myDevice->CreateRenderTargetView(bufferTexture.Get(), nullptr, myRTVs[GBufferTexture::GB_AMBIENTOCCULUSION].GetAddressOf());
	DX11::myDevice->CreateShaderResourceView(bufferTexture.Get(), nullptr, mySRVs[GBufferTexture::GB_AMBIENTOCCULUSION].GetAddressOf());
}

void GBuffer::SetAsTarget() const
{
	ID3D11RenderTargetView* rtvList[GBufferTexture::GB_COUNT];
	for (int i = 0; i < myRTVs.size(); i++)
	{
		rtvList[i] = myRTVs[i].Get();
	}

	DX11::myContext->OMSetRenderTargets(GBufferTexture::GB_COUNT, &rtvList[0], DX11::myDepthBuffer.Get());
}

void GBuffer::ClearTarget() const
{
	ID3D11RenderTargetView* rtvList[GBufferTexture::GB_COUNT];
	for (int i = 0; i < myRTVs.size(); i++)
	{
		rtvList[i] = nullptr;
	}

	DX11::myContext->OMSetRenderTargets(GBufferTexture::GB_COUNT, &rtvList[0], DX11::myDepthBuffer.Get());
}

void GBuffer::SetAsResource(unsigned int aStartSlot) const
{
	ID3D11ShaderResourceView* srvList[GBufferTexture::GB_COUNT];
	for (uint16_t t = 0; t < mySRVs.size(); t++)
	{
		srvList[t] = mySRVs[t].Get();
	}

	DX11::myContext->PSSetShaderResources(aStartSlot, GBufferTexture::GB_COUNT, &srvList[0]);
}

void GBuffer::ClearResource(unsigned int aStartSlot) const
{
	ID3D11ShaderResourceView* srvList[GBufferTexture::GB_COUNT];
	for (uint16_t t = 0; t < mySRVs.size(); t++)
	{
		srvList[t] = nullptr;
	}

	DX11::myContext->PSSetShaderResources(aStartSlot, GBufferTexture::GB_COUNT, &srvList[0]);
}

void GBuffer::Clear() const
{
	std::array<float, 4> color{ 0.0f, 0.0f, 0.0f, 0.0f };
	for (uint8_t t = 0; t < myRTVs.size(); t++)
	{
		DX11::myContext->ClearRenderTargetView(myRTVs[t].Get(), &color[0]);
	}
}