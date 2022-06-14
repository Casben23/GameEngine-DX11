#include "GraphicsEngine.pch.h"
#include "TextureAssetHandler.h"

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
    }
    return false;
}
