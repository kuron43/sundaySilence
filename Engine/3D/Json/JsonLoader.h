#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include <sstream>
#include <fstream>

#include "Affin.h"
#include <DirectXMath.h>
#include <map>

#include "Model.h"
#include "Object3d.h"

// レベルデータ
struct LevelData {

	struct ObjectData {
		// ファイル名
		std::string fileName;
		// 平行移動
		Vector3 translation;
		// 回転角
		Vector3 rotation;
		// スケーリング
		Vector3 scaling;
	};

	// オブジェクト配列
	std::vector<ObjectData> objects;
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

	static LevelData* LoadJsonFile(const string& filename);
	//void NodeRecursive(nlohmann::json deserialized, LevelData* levelData);

	//void MakeScene(LevelData* leveData);

private:
	std::map<std::string,Model*> models;
};

