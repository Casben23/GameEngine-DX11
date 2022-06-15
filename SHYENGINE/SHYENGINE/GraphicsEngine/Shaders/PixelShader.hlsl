#include "ShaderStructs.hlsli"
PixelOutput main(VertexToPixel input)
{
    PixelOutput result;

    float3 debugNormal = input.myNormal;
    const float signedLength = (input.myNormal.r + input.myNormal.g + input.myNormal.b) / 3;
    if (signedLength < 0) 
    {
        debugNormal = float3(1 - abs(debugNormal));
    }
	
    result.myColor.rgb = debugNormal;
	result.myColor.a = 1;

    return result;
}