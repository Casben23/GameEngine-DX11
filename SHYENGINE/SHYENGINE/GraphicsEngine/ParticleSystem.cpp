#include "GraphicsEngine.pch.h"
#include "ParticleSystem.h"

void ParticleSystem::Update(float aDeltaTime)
{
	for (ParticleEmitter& e : myEmitters)
		e.Update(aDeltaTime);
}
