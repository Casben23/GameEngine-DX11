SamplerState defaultSampler : register(s0);

Texture2D albedoTexture : register(t0);
Texture2D normalTexture : register(t1);
Texture2D materialTexture : register(t2);
Texture2D vertexNormalTexture : register(t3);
Texture2D worldPositionTexture : register(t4);
Texture2D ambientOcclusionTexture : register(t5);

TextureCube environmentTexture : register(t10);

cbuffer FrameBuffer : register(b0)
{
	float4x4 FB_ToView;
	float4x4 FB_ToProjection;
    float3 FB_CamTranslation;
    uint FB_Padding;
}

cbuffer ObjectBuffer : register (b1)
{
	float4x4 OB_ToWorld;
	bool OB_HasBones;
	float3 OB_padding;
	float4x4 OB_BoneData[128];
}

cbuffer MaterialBuffer : register(b2)
{
	float3 MB_Albedo;
	float padding1;
	float3 MB_Normal;
	float padding2;
} 

struct DeferredPixelOutput
{
    float4 myColor : SV_TARGET;
};

struct DeferredVertexInput
{
    unsigned int myIndex : SV_VertexID;
};

struct DeferredVertexToPixel
{
    float4 Position : SV_Position;
    float2 UV : TEXCOORD;
};

struct GBufferOutput
{
    float4 Albedo : SV_TARGET0;
    float4 Normal : SV_TARGET1;
    float4 Material : SV_TARGET2;
	
    float4 VertexNormal : SV_TARGET3;
	
    float4 WorldPosition : SV_TARGET4;
	
    float AmbientOcclusion : SV_TARGET5;
};

struct VertexInput
{
	float4 myPosition		: POSITION;
	float4 myVxColor		: COLOR0;
	float4 myVxColor2		: COLOR1;
	float4 myVxColor3		: COLOR2;
	float4 myVxColor4		: COLOR3;
	float2 myUV				: UV0;
	float2 myUV2			: UV1;
	float2 myUV3			: UV2;
	float2 myUV4			: UV3;
	uint4 myBoneIDs			: BONEIDS;
	float4 myBoneWeights	: BONEWEIGHTS;
	float3 myTangent		: TANGENT;
    float3 myBinormal		: BINORMAL;
	float3 myNormal			: NORMAL;
};

struct VertexToPixel
{
	float4 myPosition		: SV_POSITION;
    float4 myVxPosition		: POSITION;
	float4 myVxColor		: COLOR0;
	float4 myVxColor2		: COLOR1;
	float4 myVxColor3		: COLOR2;
	float4 myVxColor4		: COLOR3;
	float2 myUV				: UV0;
	float2 myUV2			: UV1;
	float2 myUV3			: UV2;
	float2 myUV4			: UV3;
	uint4 myBoneIDs			: BONEIDS;
	float4 myBoneWeights	: BONEWEIGHTS;
	float3 myTangent		: TANGENT;
    float3 myBinormal		: BINORMAL;
	float3 myNormal			: NORMAL;
};

struct PixelOutput
{
	float4 myColor : SV_TARGET;
};


