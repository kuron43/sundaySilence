#pragma once
#include "IScene.h"
#include "JsonLoader.h"
#include "SceneIntegrate.h"

class TitleScene :public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	
	TitleScene(SceneManager* controller, SceneObjects* objects);
	~TitleScene() override;

	void Initialize() override;
	void Update(Input* input) override;
	void Draw() override;
private:
	//代入演算子削除
	TitleScene& operator=(const TitleScene&) = delete;
	//コピーコンストラクタ削除
	TitleScene(const TitleScene&) = delete;

	Vector3 camposEye = { 0.0f,40.0f,-90.01f };
	Vector3 camposTar = { 0,0,0 };

	LevelData* leveData = nullptr;
	ParticleManager* particle_ = nullptr;
public:
	
private://リソース
	std::unique_ptr <Sprite> title_;
	Vector2 titlePos = { 20.0f,10.0f };
	std::unique_ptr <Sprite> titleButton_;
	std::unique_ptr <Sprite> red_;

	uint32_t titleTime_;
	float sinMoveTitle;
};