#pragma once
#include "Transform.h"

class SceneObject
{
protected:
	Transform myTransform;

public:
	SceneObject() = default;
	virtual ~SceneObject() = default;

	FORCEINLINE Transform& GetTransform() { return myTransform; }
};

