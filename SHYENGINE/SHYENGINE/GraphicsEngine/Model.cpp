#include "GraphicsEngine.pch.h"
#include "Model.h"

bool Model::Init(std::vector<MeshData> aMeshData, const char* aPath)
{
	myMeshData = aMeshData;

	return true;
}

bool Model::Init(std::vector<MeshData> aMeshData, const char* aPath, Skeleton& aSkeleton)
{
	myMeshData = aMeshData;
	mySkeleton = aSkeleton;
	return false;
}
