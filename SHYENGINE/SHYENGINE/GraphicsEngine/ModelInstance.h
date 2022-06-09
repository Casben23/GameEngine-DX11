#pragma once
#include <iostream>
#include "Model.h"
#include "SceneObject.h"
#include <array>
class ModelInstance : public SceneObject
{
	std::shared_ptr<Model> myModel;
	Animation myCurrentAnimation;

	float myTimer = 0.0f;

	std::array<Matrix4x4f, 128> myBoneTransforms;

public:

	ModelInstance() = default;

	void Init(std::shared_ptr<Model> aModel);
	void Update();
	void UpdateAnimationHierarchy(size_t aCurrentFrame, unsigned aBoneIdx, const Animation* anAnimation, Matrix4x4f& aParentTransform, Matrix4x4f* outBoneTransforms);

	FORCEINLINE std::shared_ptr<Model> GetModel() { return myModel; }
	FORCEINLINE std::array<Matrix4x4f, 128>& GetBoneTransforms() { return myBoneTransforms; }
	FORCEINLINE Model::MeshData const& GetMeshData(unsigned int anIndex) const { return myModel->GetMeshData(anIndex); }
	FORCEINLINE size_t GetNumMeshes() const { return myModel->GetNumMeshes(); }
};

