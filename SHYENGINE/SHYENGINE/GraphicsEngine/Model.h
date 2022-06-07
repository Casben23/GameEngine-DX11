#pragma once
#include "Math/Matrix/Vector.hpp"
#include "DX11.h"
#include <vector>
#include "SceneObject.h"

class Material;

struct Vertex
{
	CommonUtilities::Vector4<float> myPosition = { 0,0,0,1 };

	CommonUtilities::Vector4<float> myVertexColors[4] =
	{
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	};
};


class Model : public SceneObject
{
public:
	struct MeshData
	{
		ComPtr<ID3D11Buffer> myVertexBuffer;
		ComPtr<ID3D11Buffer> myIndexBuffer;

		std::shared_ptr<Material> myMaterial;

		UINT myPrimitiveTopology;
		UINT myNumberOfVertices;
		UINT myNumberOfIndices;
		UINT myStride;
		UINT myOffset;

		ComPtr<ID3D11InputLayout> myInputLayout;
		ComPtr<ID3D11VertexShader> myVertexShader;
		ComPtr<ID3D11PixelShader> myPixelShader;
	};

	bool Init(std::vector<MeshData> aMeshData, const char* aPath);
	
	FORCEINLINE MeshData const& GetMeshData(unsigned int anIndex) const { return myMeshData[anIndex]; }
	FORCEINLINE size_t const GetNumMeshes() { return myMeshData.size(); }
	FORCEINLINE std::wstring const& GetName() const { return myName; }

private:
	std::vector<MeshData> myMeshData;
	std::wstring myPath;
	std::wstring myName;
};

