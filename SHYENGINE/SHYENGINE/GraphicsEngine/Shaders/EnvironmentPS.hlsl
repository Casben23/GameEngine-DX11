#include "PBRFunctions.hlsli"
#include "LightBuffer.hlsli"
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
    float3 directLighting = EvaluateDirectionalLight(diffuseColor, specularColor, pixelNormal, roughness, LB_DirectionalLight.Color, LB_DirectionalLight.Intensity, -LB_DirectionalLight.Direction, toEye);
    
    float3 pointLight = 0;
    float3 spotLight = 0;
    
    for (unsigned int l = 0; l < LB_NumLights; l++)
    {
        const LightData Light = LB_Lights[l];
        switch (Light.LightType)
        {
            default:
                break;
            case 0:
                break;
            case 1:
                pointLight += EvaluatePointLight(diffuseColor, specularColor, pixelNormal, material.g, Light.Color, Light.Intensity, Light.Range, Light.Position, toEye, worldPosition);
                break;
            case 2:
                spotLight += EvaluateSpotLight(diffuseColor, specularColor, pixelNormal, material.g, Light.Color, Light.Intensity, Light.Range, Light.Position, Light.Direction, Light.SpotOuterRadius, Light.SpotInnerRadius, toEye, input.Position.xyz);
                break;

        }
    }
    
    if (LB_DirectionalLight.myCastingShadows)
    {
        const float4 worldToLightView = mul(LB_DirectionalLight.View, worldPosition);
        const float4 lightViewToLightProj = mul(LB_DirectionalLight.Projection, worldToLightView);
        
        float2 projectedTexCoord;
        projectedTexCoord.x = lightViewToLightProj.x / lightViewToLightProj.w / 2.0f + 0.5f;
        projectedTexCoord.y = -lightViewToLightProj.y / lightViewToLightProj.w / 2.0f + 0.5f;
        
        if (saturate(projectedTexCoord.x) == projectedTexCoord.x && saturate(projectedTexCoord.y) == projectedTexCoord.y)
        {
            const float shadowBias = 0.0005f;
            
            const float shadow = 0.0f;
            
            const float viewDepth = (lightViewToLightProj.z / lightViewToLightProj.w) - shadowBias;
            
            const float lightDepth = dirLightShadowMap.Sample(pointClampSampler, projectedTexCoord).r;
            
            if (lightDepth < viewDepth)
            {
                directLighting *= shadow;
            }
        }
    }
    
    
    result.myColor.rgb = LinearToGamma(directLighting + ambientLighting + pointLight + spotLight);
    result.myColor.a = 1;

    return result;
}