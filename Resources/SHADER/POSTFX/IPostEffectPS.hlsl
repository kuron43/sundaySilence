#include"PostEffect.hlsli"


Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1); // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
    float d = distance(drawUV, pickUV);
    return exp(-(d * d) / (2 * sigma * sigma));
}

float4 main(VSOutput input) : SV_TARGET
{

    float offsetU = 1 / 1280.0f;
    float offsetV = 1 / 720.0f;

    if (shadeNumber == 0)
    {
        float4 texcolor = tex0.Sample(smp, input.uv);
        return float4(texcolor.rgb, 1);
        //return texcolor;
    }
    else if (shadeNumber == 1)
    {
        float totalWeight = 0, _Sigma = 0.005, _StepWidth = 0.001;
        float4 col = float4(0, 0, 0, 1);

        for (float py = -_Sigma * 2; py <= _Sigma * 2; py += _StepWidth)
        {
            for (float px = -_Sigma * 2; px <= _Sigma * 2; px += _StepWidth)
            {

                float2 _pickUV = input.uv + float2(px, py);
                float weight = Gaussian(input.uv, _pickUV, _Sigma);

                col += tex0.Sample(smp, _pickUV) * weight;
                totalWeight += weight;
            }
        }
        col.rgb = col.rgb / totalWeight;
        col.a = 1;
        return col;
    }
    if (shadeNumber == 2)
    {
        float4 tax0 = tex0.Sample(smp, input.uv)/2;
        float4 tax1 = tex1.Sample(smp, input.uv)/2;
        
        return float4(tax0.rgb + tax1.rgb,1);
       
    }
    if (shadeNumber == 3)
    {
        float2 samplePoint = input.uv;
        float4 Tex = tex0.Sample(smp, samplePoint);
        float vignette = length(float2(0.5, 0.5) - input.uv);
        vignette = clamp(vignette - 0.5, 0, 1);
        Tex.rgb -= vignette;
        return float4(Tex.rgb, 1.0);
       
    }
    return float4(0, 0, 0, 1);
}