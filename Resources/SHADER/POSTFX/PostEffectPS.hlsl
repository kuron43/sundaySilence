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
    else if (shadeNumber == 1)      // CG4 評価課題用
    {
        float4 colortex0 = tex0.Sample(smp, input.uv);
        //float4 colortex1 = tex1.Sample(smp, input.uv);

		//掛ける強度
        int kernelSize = KernelSize;

		// 平均値を計算するための総和
        float4 sum = float4(0, 0, 0, 0);

		// カーネルサイズの範囲内でピクセルをイテレート
        for (int y = -kernelSize; y <= kernelSize; ++y)
        {
            for (int x = -kernelSize; x <= kernelSize; ++x)
            {
                float2 offset = float2(x, y) * float2(offsetU, offsetV);
                float4 colortex0 = tex0.Sample(smp, input.uv + offset);
                sum += colortex0;
            }
        }

		// 総和をカーネルサイズで割ることで平均値を計算
        float kernelArea = (2 * kernelSize + 1) * (2 * kernelSize + 1);
        float4 averageColor = sum / kernelArea;

        float4 col = averageColor;

        if (fmod(input.uv.y, 0.1f) < 0.05f)
        {
            col = 1 - colortex0;
        }
        return float4(col.rgb, 1);
    }
    else if (shadeNumber == 2)
    {
        float2 uv = input.uv;
        float2 direction = uv - center;
        float2 step = direction / float(samples);

        float4 col = tex0.Sample(smp, uv);
        float totalWeight = 0.5;
        for (int i = 1; i < samples; ++i)
        {
            float weight = (float(samples) - float(i)) / float(samples);
            float2 sampleUV = uv - step * float(i) * intensity;
            col += tex0.Sample(smp, sampleUV) * weight;
            totalWeight += weight;
        }

        col /= totalWeight;
        return float4(col.rgb, 1);
    }
    else if (shadeNumber == 3)
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
    if (shadeNumber == 4)
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