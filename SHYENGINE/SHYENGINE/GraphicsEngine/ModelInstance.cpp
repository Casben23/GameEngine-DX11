#include "GraphicsEngine.pch.h"
#include "ModelInstance.h"
#include "Timer.h"
void ModelInstance::Init(std::shared_ptr<Model> aModel)
{
	myModel = aModel;
	if (myModel->GetSkeleton()->GetRoot())
	{
		myCurrentAnimation = myModel->GetSkeleton()->myAnimations.at(std::wstring(myModel->GetSkeleton()->myName.begin(), myModel->GetSkeleton()->myName.end()));
		myCurrentAnimation.myAnimationState = Animation::AnimationState::Playing;
	}
	else
	{
		myCurrentAnimation.myAnimationState = Animation::AnimationState::Finished;
	}
}

void ModelInstance::Update(float aDeltaTime) 
{
	if (myCurrentAnimation.myAnimationState == Animation::AnimationState::Playing)
	{
		float frameTime = 1.f / myCurrentAnimation.myFramesPerSecond;
		myTimer += Timer::GetDeltaTime();

		if (Timer::GetDeltaTime() > (frameTime * myCurrentAnimation.myCurrentFrame))
		{
			if (myCurrentAnimation.myCurrentFrame < myCurrentAnimation.myLength - 1)
			{
				myCurrentAnimation.myCurrentFrame++;
			}
			else
			{
				myCurrentAnimation.myCurrentFrame = 1;
				myTimer = 0.f;
			}
		}

		Matrix4x4f identity = Matrix4x4f();
		UpdateAnimationHierarchy(myCurrentAnimation.myCurrentFrame, 0, &myCurrentAnimation, identity, &GetBoneTransforms()[0]);
	}
}

void ModelInstance::UpdateAnimationHierarchy(size_t aCurrentFrame, unsigned aBoneIdx, const Animation* anAnimation, Matrix4x4f& aParentTransform, Matrix4x4f* outBoneTransforms)
{
	if (myCurrentAnimation.myFrames.size() <= 0) return;

	auto bones = myModel->GetSkeleton()->myBones;
	outBoneTransforms[aBoneIdx] = aParentTransform * anAnimation->myFrames[anAnimation->myCurrentFrame].myLocalTransforms[aBoneIdx];

	for (auto bone : bones[aBoneIdx].myChildren)
	{
		UpdateAnimationHierarchy(aCurrentFrame, bone, anAnimation, GetBoneTransforms()[aBoneIdx], outBoneTransforms);
	}

	outBoneTransforms[aBoneIdx] *= bones[aBoneIdx].myBindPoseInverse;
}
