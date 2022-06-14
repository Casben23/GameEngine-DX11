#include "ShaderStructs.hlsli"
PixelOutput main(VertexToPixel input)
{
    PixelOutput result;

	/*const float average = (input.myVxColor.r + input.myVxColor.b + input.myVxColor.g) / 3.0f;
    result.myColor = average * float4(MB_Albedo, 1);*/

    result.myColor.rgb = albedoTexture.Sample(defaultSampler, input.myUV).rgb;
    result.myColor.a = 1;

    return result;
}