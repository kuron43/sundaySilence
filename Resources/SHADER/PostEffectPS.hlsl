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
        float4 colortex0 = tex0.Sample(smp, input.uv);
        float4 colortex1 = tex1.Sample(smp, input.uv);

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

        float4 color = averageColor;

        if (fmod(input.uv.y, 0.1f) < 0.05f)
        {
            color = colortex1;
        }
        return float4(color.rgb, 1);
    }
    else if (shadeNumber == 1)
    {
        float2 uv = input.uv;
        float2 direction = uv - center;
        float2 step = direction / float(samples);

        float4 result = tex0.Sample(smp, uv);
        float totalWeight = 1.0;
        for (int i = 1; i < samples; ++i)
        {
            float weight = (float(samples) - float(i)) / float(samples);
            float2 sampleUV = uv - step * float(i) * intensity;
            result += tex0.Sample(smp, sampleUV) * weight;
            totalWeight += weight;
        }

        result /= totalWeight;
        return result;
    }
    else if (shadeNumber == 2)
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
    return float4(1, 1, 1, 1);
}