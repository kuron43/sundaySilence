#pragma once
/**
 * @file IPosteffect.h
 * @brief 基底ポストエフェクトクラス
 */
#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4514)
#include <DirectXTex.h>
#include <array>
#include <memory>
#include <string>
#pragma warning(pop)

#include"DirectXCommon.h"
#include "WinApp.h"
#include "Affin.h"
class IPostEffect
{
public:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	/// <summary>
	/// 頂点データ構造体
	/// </summary>
	struct VertexPosUv {
		Vector3 pos; // xyz座標
		Vector2 uv;  // uv座標

	};

	/// <summary>
	/// 定数バッファ用データ構造体
	/// </summary>
	struct ConstBufferData {
		Vector4 color; // 色 (RGBA)
		Matrix4 mat;   // ３Ｄ変換行列
	};

	//デフォルトテクスチャ格納ディレクトリ
	static const std::wstring kDefaultShaderDirectoryPath;
	static const std::wstring kShaderExtention;
	HRESULT result;
public:

	static void Initialize(DirectXCommon* dxCommon, const std::wstring& fileName);

	static void Finalize();

	/// <summary>
	/// パイプライン生成
	/// </summary>
	static void CreatGraphicsPipeline(const std::wstring& fileName);

	/// <summary>
	/// シーン描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	static void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// シーン描画処理
	/// </summary>
	static void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// シーン描画後処理
	/// </summary>
	/// <param name="cmdList">コマンド処理</param>
	static void PostDrawScene();

private://静的メンバ変数
	static const Vector4 clearColor;

	static ID3D12Device* device_;

	static ID3D12GraphicsCommandList* commandList;

	static VertexPosUv vertices[4];

	static VertexPosUv* vertMap;

	static ComPtr<ID3D12Resource> vertBuff;	//頂点バッファ

	//頂点バッファビューの作成
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	static ComPtr<ID3D12Resource> texBuff;

	static ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//深度バッファ
	static ComPtr<ID3D12Resource> depthBuff;
	//RTV用のデスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV用のデスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeapDSV;

	static ComPtr<ID3D12PipelineState> pipelineState;
	static ComPtr<ID3D12RootSignature> rootSignature;
private:
	// 定数バッファ
	static ComPtr<ID3D12Resource> constDataBuff_;


	//コピーコンストラクタ・代入演算子削除
	IPostEffect& operator=(const IPostEffect&) = delete;
	IPostEffect(const IPostEffect&) = delete;
};

