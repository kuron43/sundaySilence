#pragma once

#include <vector>
#include <d3d12.h>
#include <string>
#include <wrl.h>
#include <d3dx12.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Affin.h"


class Model
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略

public: // サブクラス
// 頂点データ構造体
	struct VertexPosNormalUv
	{
		Vector3 pos; // xyz座標
		Vector3 normal; // 法線ベクトル
		Vector2 uv;  // uv座標
	};

	struct ConstBufferDataB1 {
		Vector3 ambient;	//アンビエント係数
		float pad1;			//パティング
		Vector3 diffuse;	//ディフーズ係数
		float pad2;			//パティング
		Vector3 specular;	//スペキュラー係数
		float alpha;		//アルファ
	};



public://静的メンバ関数
	//OBJファイルから3Dモデルを読み込む
	static Model* LoadFromOBJ(const std::string& modelname);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial);

	/// <summary>
	//マテリアル読み込み
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	//setter
	static void SetDevice(ID3D12Device* device) { Model::device = device; }

	

private://メンバ変数
	
	//OBJファイルから3Dモデルを読み込む(非公開)
	void LoadFromOBJInternal(const std::string& modelname);
		
	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	void InitializeDescriptorHeap();
		
	//各種バッファ生成
	void CreateBuffers();

private:

	ComPtr<ID3D12Resource> constBuffB1; // 定数バッファ	

	// デバイス
	static ComPtr<ID3D12Device> device;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(GPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView;


	// 頂点データ配列
	std::vector<VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	std::vector<unsigned short> indices;

	//マテリアル
	struct Material
	{
		std::string name; //マテリアル名
		Vector3 ambient; //アンビエント影響度
		Vector3 diffuse; //ディフューズ影響度
		Vector3 specular; //スペキュラー影響度
		float alpha; //アルファ
		std::string textureFilename; //テクスチャファイル名
		//コンストラクタ
		Material() {
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};

	Material material;

};

