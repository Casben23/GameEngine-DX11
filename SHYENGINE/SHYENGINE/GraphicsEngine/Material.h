#pragma once
#include "Math/Matrix/Vector.hpp"

class Material
{
	std::wstring myName;
	Vector3f myAlbedo;

public:
	Material();
	virtual ~Material() = default;

	void Init(const std::wstring aName, const Vector3f& aAlbedo);

	FORCEINLINE const std::wstring& GetName() const { return myName; };
	FORCEINLINE const Vector3f& GetAlbedo() const { return myAlbedo; };
	
};

