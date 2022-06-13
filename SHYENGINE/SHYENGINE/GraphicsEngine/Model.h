#pragma once
#include "Math/Matrix/Vector.hpp"
#include "DX11.h"
#include <vector>
#include "SceneObject.h"
#include "Skeleton.hpp"

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

	Vector2f UVs[4]
	{
		{0,0},
		{0,0},
		{0,0},
		{0,0}
	};
	
	CommonUtilities::Vector4<unsigned int> myBoneIDs = { 0,0,0,0 };
	CommonUtilities::Vector4<float> myBoneWeights = { 0,0,0,0 };
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
	bool Init(std::vector<MeshData> aMeshData, const char* aPath, Skeleton& aSkeleton);
	void AddAnimation(Animation aAnimation) { mySkeleton.myAnimations.insert({ aAnimation.myName, aAnimation }); }
	
	FORCEINLINE const Skeleton* GetSkeleton() const { return &mySkeleton; }
	FORCEINLINE MeshData const& GetMeshData(unsigned int anIndex) const { return myMeshData[anIndex]; }
	FORCEINLINE size_t const GetNumMeshes() { return myMeshData.size(); }
	FORCEINLINE std::wstring const& GetName() const { return myName; }

private:
	
	Skeleton mySkeleton;

	std::vector<MeshData> myMeshData;
	std::wstring myPath;
	std::wstring myName;
};

