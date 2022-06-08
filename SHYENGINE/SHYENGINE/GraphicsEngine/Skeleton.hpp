#pragma once
#include "Math/Matrix/Matrix4x4.hpp"
#include <unordered_map>
#include <memory>
#include <vector>
#include <wrl.h>
#include "FBXImporter.h"

struct Animation
{
	enum class AnimationState
	{
		Playing,
		Paused,
		Finished
	}myAnimationState;

	struct Frame
	{
		std::vector<Matrix4x4f> myLocalTransforms;
	};
	
	std::vector<Frame> myFrames;
	
	size_t myCurrentFrame;
	unsigned int myLength;
	float myDuration;
	float myFramesPerSecond;
	std::wstring myName;
};

struct Skeleton
{
	std::string myName;
	
	struct Bone
	{
		Matrix4x4f myBindPoseInverse;
		int myParent;
		std::vector<unsigned int> myChildren;
		std::string myName;
	};
	
	std::vector<Bone> myBones;
	
	std::unordered_map<std::string, size_t> myBoneNameToIndex;
	std::vector<std::string> myBoneName;
	
	std::unordered_map<std::wstring, Animation> myAnimations;
	
	FORCEINLINE const Bone* GetRoot() const
	{ 
		if (!myBones.empty()) { return &myBones[0]; return nullptr; }
	}
};