#pragma once
#include <array>
#include <wrl.h>
#include "DX11.h"
using namespace Microsoft::WRL;

class GBuffer
{
	friend class TextureAssetHandler;

public:
	enum GBufferTexture {
		GB_ALBEDO,
		GB_NORMAL,
		GB_MATERIAL,
		GB_VERTEXNORMAL,
		GB_POSITION,
		GB_AMBIENTOCCULUSION,
		GB_COUNT
	};

	GBuffer(float aWidth, float aHeight);

	void SetAsTarget() const;
	void ClearTarget() const;
	void SetAsResource(unsigned int aStartSlot) const;
	void ClearResource(unsigned int aStartSlot) const;
	void Clear() const;
	ComPtr<ID3D11RenderTargetView> GBufferRTV;

private:
	std::array<ComPtr<ID3D11RenderTargetView>,
		GBufferTexture::GB_COUNT>
		myRTVs;
	std::array<ComPtr<ID3D11ShaderResourceView>,
		GBufferTexture::GB_COUNT>
		mySRVs;

};

