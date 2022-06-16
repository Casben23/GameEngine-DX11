#pragma once
#include <vector>
#include <iostream>
#include "SceneObject.h"
#include "Camera.h"
#include "Model.h"
#include "ModelInstance.h"
#include "Light.h"

class Scene
{
	std::vector<std::shared_ptr<ModelInstance>> mySceneObjects;

	std::shared_ptr<Camera> myMainCamera;

public:



	//template<typename T>
	void AddGameObject(std::shared_ptr<ModelInstance> aSceneObject)
	{
		mySceneObjects.push_back(std::move(aSceneObject));
	}

	std::vector<std::shared_ptr<ModelInstance>> GetSceneObjects() { return mySceneObjects; }
	std::shared_ptr<Camera> GetMainCamera() { return myMainCamera; }

	void SetCamera(std::shared_ptr<Camera> aCamera) { myMainCamera = aCamera; }
};

