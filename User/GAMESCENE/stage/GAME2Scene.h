#pragma once
#include "IScene.h"

#include "JsonLoader.h"
#include "SceneIntegrate.h"

class GAME2Scene :
    public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	GAME2Scene(SceneManager* controller, SceneObjects* objects);
	~GAME2Scene() override;

	//void Cleate(SceneManager& controller) override;
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力管理クラス</param>
	void Update(Input* input) override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private:
	bool stageClear = false;
	bool stageFailed = false;

	// カメラ座標
	Vector3 camposEye = { 0.0f,100.0f,-10.0f };
	Vector3 camposTar = { 0,0,0 };

public:


	// json
	//Model* modelcube = nullptr;
	//Model* modelREX = nullptr;

	LevelData* leveData = nullptr;
	//std::map<std::string, Model*> jsonModels;
	//std::vector<Object3d*> JsonObjects;

};

