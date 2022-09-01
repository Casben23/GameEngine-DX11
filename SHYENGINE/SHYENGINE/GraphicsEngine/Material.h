#pragma once
#include "Math/Matrix/Vector.hpp"
#include "Texture.h"

namespace MaterialTextureChannel
{
	enum
	{
		Albedo,
		Normal,
		Material,
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
		float padding1;
		Vector3f myNormal;
		float padding2;
	};

	Material();
	virtual ~Material() = default;

	void Init(const std::wstring aName, const Vector3f& aAlbedo);

	FORCEINLINE const std::wstring& GetName() const { return myName; };
	FORCEINLINE const Vector3f& GetAlbedo() const { return myMaterialData.myAlbedo; };
	
	void SetAlbedoTexture(std::shared_ptr<Texture> aTexture);
	void SetNormalTexture(std::shared_ptr<Texture> aTexture);
	void SetMaterialTexture(std::shared_ptr<Texture> aTexture);

	void SetAsResource(ComPtr<ID3D11Resource> aMaterialBuffer);

private:
	MaterialData myMaterialData;
	std::array<std::shared_ptr<Texture>, MaterialTextureChannel::Count> myTextures;
};

