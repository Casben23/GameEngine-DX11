#include "ShaderStructs.hlsli"

VertexToPixel main(VertexInput input)
{
	VertexToPixel result;
	
	float4 vertexPosition = input.myPosition;
	if (OB_HasBones)
	{
		vertexPosition = 0;
		
		vertexPosition += input.myBoneWeights.x * mul(input.myPosition, OB_BoneData[input.myBoneIDs.x]);
		vertexPosition += input.myBoneWeights.y * mul(input.myPosition, OB_BoneData[input.myBoneIDs.y]);
		vertexPosition += input.myBoneWeights.z * mul(input.myPosition, OB_BoneData[input.myBoneIDs.z]);
		vertexPosition += input.myBoneWeights.w * mul(input.myPosition, OB_BoneData[input.myBoneIDs.w]);
	}
	
	const float4 vertexObjectPosition = input.myPosition;
	const float4 vertexWorldPosition = mul(OB_ToWorld, vertexPosition);
	const float4 vertexViewPosition = mul(FB_ToView, vertexWorldPosition);
	const float4 vertexProjectonPosition = mul(FB_ToProjection, vertexViewPosition); 

	result.myPosition = vertexProjectonPosition;

	result.myVxColor = input.myVxColor;
	result.myVxColor2 = input.myVxColor2;
	result.myVxColor3 = input.myVxColor3;
	result.myVxColor4 = input.myVxColor4;

	result.myUV = input.myUV;
	result.myUV2 = input.myUV2;
	result.myUV3 = input.myUV3;
	result.myUV4 = input.myUV4;

	return result;
}