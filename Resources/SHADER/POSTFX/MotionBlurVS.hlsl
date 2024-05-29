#include"MotionBlur.hlsli"

VS_OUTPUT mainVS(float4 position : POSITION, float2 texCoord : TEXCOORD)
{
    VS_OUTPUT output;
    output.position = position;
    output.texCoord = texCoord;
    return output;
}