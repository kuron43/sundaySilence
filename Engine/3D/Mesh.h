#pragma once

#include "Material.h"
#include <DirectXMath.h>
#include <Windows.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <vector>
#include <wrl.h>
#include <unordered_map>
#include "Affin.h"

/// <summary>
/// 形状データ
/// </summary>
class Mesh {
private: // エイリアス
  // Microsoft::WRL::を省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // サブクラス
  // 頂点データ構造体（テクスチャあり）
	struct VertexPosNormalUv {
		Vector3 pos;    // xyz座標
		Vector3 normal; // 法線ベクトル
		Vector2 uv;     // uv座標
	};

public: // 静的メンバ関数
  /// <summary>
  /// 静的初期化
  /// </summary>
  /// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device* device);

private: // 静的メンバ変数
  // デバイス
	static ID3D12Device* device_;

public: // メンバ関数
  /// <summary>
  /// 名前を取得
  /// </summary>
  /// <returns>名前</returns>
	const std::string& GetName() { return name_; }

	/// <summary>
	/// 名前をセット
	/// </summary>
	/// <param name="name">名前</param>
	void SetName(const std::string& name);

	/// <summary>
	/// 頂点データの追加
	/// </summary>
	/// <param name="vertex">頂点データ</param>
	void AddVertex(const VertexPosNormalUv& vertex);

	/// <summary>
	/// 頂点インデックスの追加
	/// </summary>
	/// <param name="index">インデックス</param>
	void AddIndex(unsigned short index);

	/// <summary>
	/// マテリアルの取得
	/// </summary>
	/// <returns>マテリアル</returns>
	Material* GetMaterial() { return material_; }

	/// <summary>
	/// マテリアルの割り当て
	/// </summary>
	/// <param name="material">マテリアル</param>
	void SetMaterial(Material* material);

	/// <summary>
	/// バッファの生成
	/// </summary>
	void CreateBuffers();

	/// <summary>
	/// 頂点バッファ取得
	/// </summary>
	/// <returns>頂点バッファ</returns>
	const D3D12_VERTEX_BUFFER_VIEW& GetVBView() { return vbView; }

	/// <summary>
	/// インデックスバッファ取得
	/// </summary>
	/// <returns>インデックスバッファ</returns>
	const D3D12_INDEX_BUFFER_VIEW& GetIBView() { return ibView; }

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList">命令発行先コマンドリスト</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	//頂点法線スムージング用データ
	std::unordered_map<unsigned short, std::vector<unsigned short>>smoothData;

	/// <summary>
	/// 頂点データ数を取得
	/// </summary>
	inline size_t GetVertexCount() { return vertices.size(); }

	/// <summary>
	/// エッジ平滑化データの追加
	/// </summary>
	void AddSmoothData(unsigned short indexPosition, unsigned short indexVertex);

	/// <summary>
	/// 平滑化された頂点法線の計算
	/// </summary>
	void CalculateSmoothedVertexNormals();
private: // メンバ変数
  // 名前
	std::string name_;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	// 頂点データ配列
	std::vector<VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	std::vector<unsigned short> indices;
	// マテリアル
	Material* material_ = nullptr;
	// 頂点バッファのマップ
	VertexPosNormalUv* vertMap = nullptr;
	// インデックスバッファのマップ
	unsigned short* indexMap = nullptr;
};
