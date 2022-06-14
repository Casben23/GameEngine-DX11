#pragma once
#include "Math/Matrix/Vector.hpp"
#include "Texture.h"

namespace MaterialTextureChannel
{
	enum
	{
		Albedo,
		Count
	};
}

class Material
{
	std::wstring myName;

public:

	struct MaterialData
	{
		Vector3f myAlbedo;
		float padding;
	};

	Material();
	virtual ~Material() = default;

	void Init(const std::wstring aName, const Vector3f& aAlbedo);

	FORCEINLINE const std::wstring& GetName() const { return myName; };
	FORCEINLINE const Vector3f& GetAlbedo() const { return myMaterialData.myAlbedo; };
	
	void SetAlbedoTexture(std::shared_ptr<Texture> aTexture);
	void SetAsResource(ComPtr<ID3D11Resource> aMaterialBuffer);

private:
	MaterialData myMaterialData;
	std::array<std::shared_ptr<Texture>, MaterialTextureChannel::Count> myTextures;
};

