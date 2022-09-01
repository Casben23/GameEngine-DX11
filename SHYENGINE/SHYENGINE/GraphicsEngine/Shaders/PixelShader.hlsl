
#include "ParticleStructs.hlsli"
#include "PBRFunctions.hlsli"

PixelOutput main(VertexToPixel input)
{
    PixelOutput result;

    //const float3x3 TBN = float3x3(normalize(input.myTangent), normalize(input.myBinormal), normalize(input.myNormal));

    //// Sample our textures
    //float3 albedo = albedoTexture.Sample(defaultSampler, input.myUV).rgb;
    //float3 normalMap = normalTexture.Sample(defaultSampler, input.myUV).agr;
    //float4 material = materialTexture.Sample(defaultSampler, input.myUV);

    //// Collect material parameters
    //const float ambientOcclusion = normalMap.b;
    //const float metalness = material.r;
    //const float roughness = material.g;
    //const float emissive = material.b;
    //const float emissiveStr = material.a;
    
    //const float3 toEye = normalize(FB_CamTranslation.xyz - input.myVxPosition.xyz);
    //const float specularColor = lerp((float3) 0.04f, albedo, metalness);
    //const float3 diffuseColor = lerp((float3) 0.00f, albedo, 1 - metalness);
    
    //normalMap.z = 0;
    //normalMap = 2.0f * normalMap - 1;
    //normalMap.z = sqrt(1 - saturate(normalMap.x + normalMap.x + normalMap.y + normalMap.y));
    //normalMap = normalize(normalMap);

    //const float3 pixelNormal = normalize(mul(normalMap, TBN));
    //const float3 L = -1 * normalize(LB_Direction);
    //const float3 N = pixelNormal;
    //const float LdotN = saturate(dot(L, N));
    //const float3 C = LB_Color;
    //const float Ilight = LB_Intensity;

    //const float3 Ipixel = LdotN * C * Ilight;

    //const float3 diffuse = albedo * Ipixel;

    //const float3 environment = environmentTexture.SampleLevel(defaultSampler, input.myNormal, 5).rgb;
    //const float3 ambient = albedo * environment;
    
    //const float3 ambientLighting = EvaluateAmbience(environmentTexture, pixelNormal, input.myNormal, toEye, roughness, ambientOcclusion, diffuseColor, specularColor);
    //const float3 directLighting = EvaluateDirectionalLight(diffuseColor, specularColor, pixelNormal, roughness, LB_Color, LB_Intensity, -LB_Direction, toEye);
    
    const float3x3 TBN = float3x3(normalize(input.myTangent), normalize(input.myBinormal), normalize(input.myNormal));
    
    float3 albedo = albedoTexture.Sample(defaultSampler, input.myUV).rgb;
    float3 normalMap = normalTexture.Sample(defaultSampler, input.myUV).agr;
    float4 material = materialTexture.Sample(defaultSampler, input.myUV);
    
    // Collect material parameters
    const float ambientOcclusion = normalMap.b;
    const float metalness = material.r;
    const float roughness = material.g;
    const float emissive = material.b;
    const float emissiveStr = material.a;
    
    float3 pixelNormal = normalMap;
    pixelNormal.z = 0;
    pixelNormal = 2.0f * pixelNormal - 1;
    pixelNormal.z = sqrt(1 - saturate(pixelNormal.x + pixelNormal.x + pixelNormal.y + pixelNormal.y));
    pixelNormal = normalize(pixelNormal);
    pixelNormal = normalize(mul(pixelNormal, TBN));
    
    const float3 toEye = normalize(FB_CamTranslation.xyz - input.myVxPosition.xyz);
    const float3 specularColor = lerp((float3) 0.04f, albedo, metalness);
    const float3 diffuseColor = lerp((float3) 0.00f, albedo, 1 - metalness);
    
    const float3 ambientLighting = EvaluateAmbience(environmentTexture, pixelNormal, input.myNormal, toEye, roughness, ambientOcclusion, diffuseColor, specularColor);
    const float3 directLighting = EvaluateDirectionalLight(diffuseColor, specularColor, pixelNormal, roughness, LB_Color, LB_Intensity, -LB_Direction, toEye);
    
    result.myColor.rgb = ambientLighting + directLighting + albedo*emissive*emissiveStr;
    
    result.myColor.rgb = LinearToGamma(result.myColor.rgb); 
    
    result.myColor.rgb = albedo;
    
    result.myColor.a = 1;

    return result;
}