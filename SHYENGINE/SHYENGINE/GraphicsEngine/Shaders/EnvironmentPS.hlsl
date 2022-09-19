#include "PBRFunctions.hlsli"

DeferredPixelOutput main(DeferredVertexToPixel input)
{
    DeferredPixelOutput result;
    
    const float4 albedo = albedoTexture.Sample(defaultSampler, input.UV);
    if (albedo.a == 0)
    {
        result.myColor = 0;
        discard;
    }
    
    const float3 pixelNormal = normalTexture.Sample(defaultSampler, input.UV).rgb;
    const float4 material = materialTexture.Sample(defaultSampler, input.UV);
    const float3 vertexNormal = vertexNormalTexture.Sample(defaultSampler, input.UV).rgb;
    const float4 worldPosition = worldPositionTexture.Sample(defaultSampler, input.UV);
    const float ambientOcclusion = ambientOcclusionTexture.Sample(defaultSampler, input.UV).r;

    const float metalness = material.r;
    const float roughness = material.g;
    const float emissive = material.b;
    const float emissiveStr = material.a;
    
    const float3 toEye = normalize(FB_CamTranslation.xyz - worldPosition.xyz);
    const float3 specularColor = lerp((float3) 0.04f, albedo.xyz, metalness);
    const float3 diffuseColor = lerp((float3) 0.00f, albedo.xyz, 1 - metalness);
    
    const float3 ambientLighting = EvaluateAmbience(environmentTexture, pixelNormal, vertexNormal, toEye, roughness, ambientOcclusion, diffuseColor, specularColor);
    const float3 directLighting = EvaluateDirectionalLight(diffuseColor, specularColor, pixelNormal, roughness, LB_Color, LB_Intensity, -LB_Direction, toEye);
    
    result.myColor.rgb = LinearToGamma(directLighting + ambientLighting);
    
    result.myColor.a = 1;
    
    return result;
}