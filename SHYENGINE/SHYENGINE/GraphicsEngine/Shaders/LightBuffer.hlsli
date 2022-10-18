#define MAX_LIGHTS 8

SamplerState pointClampSampler : register(s1);

struct LightData
{
    float4x4 View;
    float4x4 Projection;
    float4 Color;
    
    float Intensity;
    float3 Direction;
    
    float Range;
    float3 Position;
    
    float Attenuation;
    float SpotInnerRadius;
    float SpotOuterRadius;
    uint LightType;
    
    bool myCastingShadows;
    
    float myNearPlane;
    float myFarPlane;
    
    float2 padding;
};

cbuffer LightBuffer : register(b3)
{
    LightData LB_DirectionalLight;
    LightData LB_Lights[MAX_LIGHTS];
    uint LB_NumLights;
    float3 LB_Padding;
}

Texture2D dirLightShadowMap;