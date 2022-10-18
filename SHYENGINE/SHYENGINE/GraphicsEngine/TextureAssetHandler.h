#pragma once
#include "Texture.h"
#include <unordered_map>
#include "DDSTextureLoader11.h"
#include "DepthStencil.h"

class TextureAssetHandler
{
	typedef std::unordered_map<std::wstring,
		std::shared_ptr<Texture>> myTextureMap;

	inline static myTextureMap myRegistry;

public:

	static std::unique_ptr<DepthStencil> CreateDepthStencil(const std::wstring& aName, size_t aWidth, size_t aHeight);
	static std::shared_ptr<Texture> GetTexture(const std::wstring& aName);
	static bool LoadTexture(const std::wstring& aFileName);

};

