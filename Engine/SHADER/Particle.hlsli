cbuffer cbuff0 : register(b0)
{
	matrix mat;
	matrix matBillboard; // ビルボード行列
};

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 pos : POSITION; // システム用頂点座標
	float scale : TEXCOORD; //スケール
};

//ジオメトリシェーダからピクセルシェーダへの出力
struct GSOutput {
	float4 svpos : SV_POSITION; // システム用頂点座標
	float2 uv  :TEXCOORD; // uv値
};