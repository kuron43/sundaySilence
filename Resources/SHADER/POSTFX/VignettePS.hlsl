#include"Vignette.hlsli"


Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    
    if (shadeNumber == 0)
    {
        float4 texcolor = tex0.Sample(smp, input.uv);
        return float4(texcolor.rgb, 1);
    }else if (shadeNumber == 1)
    {
        float2 samplePoint = input.uv;
        float4 Tex = tex0.Sample(smp, samplePoint);
        float vignette = length(float2(0.5, 0.5) - input.uv);
        vignette = clamp(vignette - 0.4, 0, 1);
        Tex.rgb += vignette * (1.0,0.0,0.0);
        return float4(Tex.rgb, 1.0);
       
    }
    return float4(0, 0, 0, 1);
}