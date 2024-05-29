struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

cbuffer ConstantBuffer : register(b0)
{
    float2 motionVector;
};

////MotionBlur.hlsl

//cbuffer ConstantBuffer : register(b0)
//{
//    matrix ViewProjection;
//    matrix PreviousViewProjection;
//    float MotionBlurAmount;
//};

//Texture2D<float4> gSceneTexture : register(t0);
//SamplerState gSampler : register(s0);

//struct VS_OUTPUT
//{
//    float4 Position : SV_POSITION;
//    float2 TexCoord : TEXCOORD0;
//};

//VS_OUTPUT VSMain(float4 position : POSITION, float2 texCoord : TEXCOORD)
//{
//    VS_OUTPUT output;
//    output.Position = mul(position, ViewProjection);
//    output.TexCoord = texCoord;
//    return output;
//}

//float4 PSMain(VS_OUTPUT input) : SV_TARGET
//{
//    float3 velocity = input.Position.xyw / input.Position.w - mul(input.Position.xyw / input.Position.w, PreviousViewProjection).xyw / mul(input.Position.xyw / input.Position.w, PreviousViewProjection).w;

//    float3 blurredColor = float3(0, 0, 0);
//    for (int i = 0; i < 10; ++i)
//    {
//        float t = i / 10.0f;
//        float2 offset = t * velocity.xy;
//        float4 sample = gSceneTexture.Sample(gSampler, input.TexCoord + offset);
//        blurredColor += sample.rgb;
//    }
//    blurredColor /= 10.0f;

//    return float4(blurredColor, 1.0f);
//}