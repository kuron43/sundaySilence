#include"MotionBlur.hlsli"
// MotionBlur.hlsl

Texture2D textureInput : register(t0);
SamplerState samplerLinear : register(s0);


float4 mainPS(VS_OUTPUT input) : SV_TARGET
{
    float2 blurTexCoord = input.texCoord - motionVector;
    float4 result = float4(0.0f, 0.0f, 0.0f, 0.0f);

    // サンプリングポイントの数と重み付けを調整することで、モーションブラーの効果を調整できます
    for (int i = -4; i <= 4; ++i)
    {
        float weight = 1.0f / 9.0f;
        result += textureInput.Sample(samplerLinear, blurTexCoord + float2(i * 0.01f, 0.0f)) * weight;
    }

    return result;
}