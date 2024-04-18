/**
 * @file FbxLoader.h
 * @brief FBXSDKのローダー
 */
#pragma once

#include <fbxsdk.h>
#include "FBXModel.h"
#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include <array>
#include <unordered_map>


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
	FBXModel* LoadModelFromFile(const string& modelName, bool isSmooth);

	/// <summary>
	/// FBXの行列XMMatrixに変換
	/// </summary>
	/// <param name="dst">書き込み先</param>
	/// <param name="src">元となるFBX行列</param>
	static void ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxAMatrix& src);

	//スキニング情報の読み取り
	void ParseSkin(FBXModel* fbxmodel, FbxMesh* fbxMesh);

	//同一頂点の法線座標かUVが重なる際の関数(新しく頂点インデックス作成)
	static bool IsExistNormalUVInfo(const std::vector<float>& vertexInfo);

	// 頂点情報生成
	static std::vector<float> CreateVertexInfo(const std::vector<float>& vertex, const FbxVector4& normalVec4, const FbxVector2& uvVec2);

	// 新しく頂点index生成
	static int CreateNewVertexIndex(const std::vector<float>& vertexInfo, const FbxVector4& normalVec4, const FbxVector2& uvVec2,
		std::vector<std::vector<float>>& vertexInfoList, int oldIndex, std::vector<std::array<int, 2>>& oldNewIndexPairList);

	// 一括にまとめたpos,norm,uv情報を整理
	static bool IsSetNormalUV(const std::vector<float> vertexInfo, const FbxVector4& normalVec4, const FbxVector2& uvVec2);

	std::vector<std::vector<int>> meshVertice;
	std::unordered_map<int, std::vector<int>> meshVerticeControlpoints;

	template<typename T>
	T Min(T a, T b) {
		return (a < b) ? a : b;
	}


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
	// ボーンデータのVSBufferへの格納
	void SetBoneDataToVertices(FbxMesh* pMesh, FBXModel* pModel, std::vector<FBXModel::VertexPosNormalUv>& vertices);
	//
	int FindJointIndexByName(const std::string& name, FBXModel* model);
	// テクスチャ読み込み
	void LoadTexture(FBXModel* fbxmodel, const std::string& fullpath);

	// ディレクトリを含んだファイルパスからファイル名を抽出する
	std::string ExtractFileName(const std::string& path);

	//頂点法線スムージング用データ
	std::unordered_map<unsigned short, std::vector<unsigned short>> smoothDate;
	bool smoothing = false;


};