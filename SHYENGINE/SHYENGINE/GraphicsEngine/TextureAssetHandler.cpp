#include "GraphicsEngine.pch.h"
#include "TextureAssetHandler.h"

std::unique_ptr<DepthStencil> TextureAssetHandler::CreateDepthStencil(const std::wstring& aName, size_t aWidth, size_t aHeight)
{
    HRESULT result = S_FALSE;

    std::unique_ptr<DepthStencil> output = std::make_unique<DepthStencil>();
    output->myName = aName;

    D3D11_TEXTURE2D_DESC desc = { 0 };
    desc.Width = static_cast<unsigned int>(aWidth);
	desc.Height = static_cast<unsigned int>(aHeight);
    desc.MipLevels = 1;
	desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS;
    desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    result = DX11::myDevice->CreateTexture2D(&desc, nullptr, reinterpret_cast<ID3D11Texture2D**>(output->myTexture.GetAddressOf()));
    if (FAILED(result))
    {
        return nullptr;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC resourceDesc = {};
    resourceDesc.Format = DXGI_FORMAT_R32_FLOAT;
    resourceDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;
    resourceDesc.Texture2D.MipLevels = desc.MipLevels;

    result = DX11::myDevice->CreateShaderResourceView(output->myTexture.Get(), &resourceDesc, output->mySRV.GetAddressOf());
    if (FAILED(result))
    {
        return nullptr;
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC depthDesc = {};
    depthDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
    depthDesc.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;

    result = DX11::myDevice->CreateDepthStencilView(output->myTexture.Get(), &depthDesc, output->myDSV.GetAddressOf());
    if (FAILED(result))
    {
        return nullptr;
    }

    output->myViewPort = D3D11_VIEWPORT({ 0.f,0.f,static_cast<float>(aWidth), static_cast<float>(aHeight),0.f,1.f });

    return output;
}

std::shared_ptr<Texture> TextureAssetHandler::GetTexture(const std::wstring& aName)
{
    return myRegistry[aName];
}

bool TextureAssetHandler::LoadTexture(const std::wstring& aFileName)
{
    if (const auto It = myRegistry.find(aFileName); It == myRegistry.end())
    {
        Texture result;
		const HRESULT createResult = DirectX::CreateDDSTextureFromFile
        (
            DX11::myDevice.Get(),
            aFileName.c_str(),
			result.myTexture.GetAddressOf(),
			result.mySRV.GetAddressOf()
        );

        if (SUCCEEDED(createResult))
        {
            myRegistry.insert({ aFileName, std::make_shared<Texture>(result) });
            return true;
        }
        return false;
    }
    return true;
}
