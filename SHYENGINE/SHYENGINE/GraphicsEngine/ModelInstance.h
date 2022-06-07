#pragma once
#include <iostream>
#include "Model.h"
#include "SceneObject.h"

class ModelInstance : public SceneObject
{
	std::shared_ptr<Model> myModel;

public:

	ModelInstance() = default;

	void Init(std::shared_ptr<Model> aModel);

	FORCEINLINE Model::MeshData const& GetMeshData(unsigned int anIndex) const { return myModel->GetMeshData(anIndex); }
	FORCEINLINE size_t GetNumMeshes() const { return myModel->GetNumMeshes(); }
};

