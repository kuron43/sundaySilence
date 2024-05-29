#pragma once
#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4820)
#pragma warning(disable: 4061)
#pragma warning(disable: 4514)
#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <DirectXMath.h>

#pragma warning(pop)

#include "Affin.h"
#include "Model.h"
#include "Object3d.h"

// レベルデータ
struct LevelData {

	struct ObjectData {
		// ファイル名
		std::string fileName;
		// buki名
		std::string weapon;
		// 平行移動
		Vector3 translation;
		// 回転角
		Vector3 rotation;
		// スケーリング
		Vector3 scaling;
	};

	// オブジェクト配列
	std::vector<ObjectData> JsonObjects;
};

class JsonLoader
{
private: // エイリアス
	// std::を省略
	using string = std::string;
public: // 定数
	// モデル格納ルートパス
	static const string baseDirectory;
	// デフォルトの読み込みディレクトリ
	static const std::string kDefaultBaseDirectory;
	// ファイル拡張子
	static const std::string kExtension;
public:
	JsonLoader();
	~JsonLoader();

	static std::unique_ptr<LevelData> LoadJsonFile(const string& filename);
	//void NodeRecursive(nlohmann::json deserialized, LevelData* levelData);

	//void MakeScene(LevelData* leveData);

private:
	// 度数法 -> ラジアン
	static float RadConvert(float value);
	//std::map<std::string,Model*> models;
};

