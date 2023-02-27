#pragma once
#include"DirectXCommon.h"
#include <DirectXTex.h>
#include <array>
#include <string>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Affin.h"


//スプライト共通部分
class SpriteCommon {
public:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	struct Vertex
	{
		Vector3 pos; // xyz座標
		Vector2 uv;  // uv座標
	};
	// 定数バッファ用データ構造体（マテリアル）
	struct ConstBufferDataMaterial {
		Vector4 color; // 色 (RGBA)
	};
	//定数バッファ用構造体（３D変換行列）
	struct ConstBufferDataTransform {
		Matrix4 mat;	//3D変換行列
	};
public:
	//初期化
	void Initialize(DirectXCommon* dxcommon);

	DirectXCommon* GetDxCommon() { return dxcommon_; }

	ID3D12RootSignature* GetRootSignature() { return rootSignature.Get(); }

	ID3D12PipelineState* GetPipelineState() { return pipelineState.Get(); }

	ID3D12DescriptorHeap* GetSrvHeap() { return srvHeap.Get(); }

	D3D12_CPU_DESCRIPTOR_HANDLE GetSrvHandle() { return srvHandle; }

	UINT GetSizeVB() { return sizeVB; }

	D3D12_RESOURCE_DESC& GetResourceDesc() { return resDesc; }

	void LoadTexture(uint32_t index, const std::string& fileName);

	void SetTextureCommands(uint32_t index);

	//Microsoft::WRL::ComPtr<ID3D12Resource> GetTexBuff(uint32_t index) { return texBuff[index]; }

	Microsoft::WRL::ComPtr<ID3D12Resource> GetTextureBuffer(uint32_t index)const { return texBuff[index].Get(); }

	//SRV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap = nullptr;
private:
	// 頂点データ
	Vertex vertices[4] = {
		// x      y     z       u     v
		{{-0.4f, -0.7f, 0.0f}, {0.0f, 1.0f}}, // 左下
		{{-0.4f, +0.7f, 0.0f}, {0.0f, 0.0f}}, // 左上
		{{+0.4f, -0.7f, 0.0f}, {1.0f, 1.0f}}, // 右下
		{{+0.4f, +0.7f, 0.0f}, {1.0f, 0.0f}}, // 右上
	};
	// SRVの最大個数
	static const size_t kMaxSRVCount = 2056;

	DirectXCommon* dxcommon_;
	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob; // ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト
	HRESULT result;

	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature;
	// パイプランステートの生成
	ComPtr<ID3D12PipelineState> pipelineState;
	std::array<ComPtr<ID3D12Resource>, kMaxSRVCount>texBuff;

	//横方向ピクセル数
	const size_t textureWidth = 256;
	//縦方向ピクセル数
	const size_t textureHeight = 256;
	//配列の要素数
	const size_t imageDataCount = textureWidth * textureHeight;

	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;

	TexMetadata metadata{};
	ScratchImage scratchImg{};
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	D3D12_RESOURCE_DESC textureResourceDesc{};

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	UINT sizeVB;

	D3D12_RESOURCE_DESC resDesc{};

	//デフォルトテクスチャ格納ディレクトリ
	static std::string kDefaultTextureDirectoryPath;

	UINT incrementSize;
};