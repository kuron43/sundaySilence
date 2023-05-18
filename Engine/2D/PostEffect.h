#pragma once
#include"DirectXCommon.h"
#include "WinApp.h"
#include <DirectXTex.h>
#include <array>
#include <string>

#include "Affin.h"

class PostEffect
{
public:
	PostEffect();
	//~PostEffect();

	void Update();

	void Draw(ID3D12GraphicsCommandList* cmdList);

public: // スプライトコモンから持ってきただけ
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
	//頂点番号
	enum VertexNumber {
		LB,//左下
		LT,//左上
		RB,//右下
		RT,//右上
	};
public:
	PostEffect(uint32_t texNum,
		Vector2 pos,
		Vector2 size,
		Vector4 color,
		Vector2 anchorP,
		bool swapLR,
		bool swapUD);

	//初期化
	void InitializeGraphicsPipeline(DirectXCommon* dxcommon);
	void Initialize( uint32_t textureIndex);

	//DirectXCommon* GetDxCommon() { return dxcommon_; }
	//ID3D12RootSignature* GetRootSignature() { return rootSignature.Get(); }
	//ID3D12PipelineState* GetPipelineState() { return pipelineState.Get(); }
	//ID3D12DescriptorHeap* GetSrvHeap() { return srvHeap.Get(); }
	//D3D12_CPU_DESCRIPTOR_HANDLE GetSrvHandle() { return srvHandle; }
	//UINT GetSizeVB() { return sizeVB; }
	//D3D12_RESOURCE_DESC& GetResourceDesc() { return resDesc; }

	void LoadTexture(uint32_t index, const std::string& fileName);

	//void SetTextureCommands(uint32_t index);

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

public: // スプライトから持ってきただけ
		//void SetPozition(const Vector2& position_);

		const Vector2& GetPosition() const { return position; }

		//void SetRotation(float rotation_);

		float GetRotation() { return rotation; }

		void SetColor(const Vector4& color_) { color = color_; }

		Vector4 GetColor() { return color; }

		void SetScale(const Vector3& scale_) { scale = scale_; }

		Vector3 GetScale() { return scale; }

		void SetAnchorPoint(const Vector2& anchorPoint_) { anchorPoint = anchorPoint_; }

		Vector2 GetAnchorPoint() { return anchorPoint; }

		//void SetTextureIndex(uint32_t texNmb) { textureIndex_ = texNmb; AdjustTextureSize(); }

		uint32_t GetTextureIndex() { return textureIndex_; }

		void SetTexSize(Vector2 texSize) { textureSize = texSize; }

		Vector2 GetTexSize() { return textureSize; }

		Vector2 GetSize() { return size_; }

		//void SetSize(Vector2 size);

		/// 上下反転の設定
		//void SetIsFlipY(bool isFlipY);

		/// 左右反転の設定
		//void SetIsFlipX(bool isFlipX);
private:

	//テクスチャサイズをイメージに合わせる
	void AdjustTextureSize();	

	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	Matrix4 matScale;//スケーリング行列
	Matrix4 matWorld;
	Matrix4 matRot;//回転行列
	Matrix4  matTrans;//平行移動行列

	//座標
	Vector3 scale{ 0.5f, 0.5f, 1.0f };

	Vector2 size_ = { 100.0f,100.0f };

	float rotation = 0.0f;
	Vector2 position = { 0.0f, 0.0f };

	Vector4 color = { 1,1,1,1 };

	Vector2 anchorPoint = { 0.0f,0.0f };

	ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;

	ConstBufferDataMaterial* constMapMaterial = nullptr;

	ComPtr<ID3D12Resource> constBuffMaterial;

	Vertex vertices_[4];

	Vertex* vertMap = nullptr;

	//テクスチャ番号
	uint32_t textureIndex_ = 0;

	//テクスチャ左上座標
	Vector2 textureLeftTop = { 0.0f,0.0f };
	//テクスチャ切り出しサイズ
	Vector2 textureSize = { 100.0f,100.0f };

	Matrix4 matProjection;

	// アンカーポイント
	Vector2 anchorpoint = { 0, 0 };

	// 頂点バッファの生成
	ComPtr<ID3D12Resource> vertBuff = nullptr;

	// 左右反転
	bool isFlipX = false;
	// 上下反転
	bool isFlipY = false;
};

