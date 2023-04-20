#pragma once

#include <fbxsdk.h>
#include "FBXModel.h"
#include <d3d12.h>
#include <d3dx12.h>
#include <string>


class FbxLoader
{
private: // エイリアス
	// std::を省略
	using string = std::string;

public: // 定数
	// モデル格納ルートパス
	static const string baseDirectory;
	// テクスチャがない場合の標準テクスチャファイル名
	static const string defaultTextureFileName;

public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device">D3D12デバイス</param>
	void Initialize(ID3D12Device* device);

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// ファイルからFBXモデル読込
	/// </summary>
	/// <param name="modelName">モデル名</param>
	FBXModel* LoadModelFromFile(const string& modelName);

	/// <summary>
	/// FBXの行列XMMatrixに変換
	/// </summary>
	/// <param name="dst">書き込み先</param>
	/// <param name="src">元となるFBX行列</param>
	static void ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxAMatrix& src);

	//スキニング情報の読み取り
	void ParseSkin(FBXModel* fbxmodel, FbxMesh* fbxMesh);


private:
	// D3D12デバイス
	ID3D12Device* device = nullptr;
	// FBXマネージャ
	FbxManager* fbxManager = nullptr;
	// FBXインポータ
	FbxImporter* fbxImporter = nullptr;

private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;

	/// <summary>
	/// 再帰的にノード構成を解析
	/// </summary>
	/// <param name="model">読み込み先モデルオブジェクト</param>
	/// <param name="fbxNode">解析対象のノード</param>
	/// <param name="parent">親ノード</param>
	void ParseNodeRecursive(FBXModel* fbxmodel, FbxNode* fbxNode, Node* parent = nullptr);

	/// <summary>
	/// メッシュ読み取り
	/// </summary>
	/// <param name="model">読み込み先モデルオブジェクト</param>
	/// <param name="fbxNode">解析対象のノード</param>
	void ParseMesh(FBXModel* fbxmodel, FbxNode* fbxNode);
	// 頂点座標読み取り
	void ParseMeshVertices(FBXModel* fbxmodel, FbxMesh* fbxMesh);
	// 面情報読み取り
	void ParseMeshFaces(FBXModel* fbxmodel, FbxMesh* fbxMesh);
	// マテリアル読み取り
	void ParseMaterial(FBXModel* fbxmodel, FbxNode* fbxNode);
	// テクスチャ読み込み
	void LoadTexture(FBXModel* fbxmodel, const std::string& fullpath);

	// ディレクトリを含んだファイルパスからファイル名を抽出する
	std::string ExtractFileName(const std::string& path);




};