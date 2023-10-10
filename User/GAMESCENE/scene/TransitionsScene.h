#pragma once
#include "IScene.h"
#include "SceneIntegrate.h"

class TransitionsScene :
    public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	TransitionsScene(SceneManager* controller, SceneObjects* objects);
	~TransitionsScene() override;

	void Initialize() override;
	void Update(Input* input) override;
	void Draw() override;


private:
	std::unique_ptr <Sprite> transSP_;
	Vector2 transSPpos_;
	Vector3 transSPscale_;
	std::unique_ptr <Sprite> titleSP_;
	Vector2 titleSPpos_;

	uint32_t sceneTimer = 0;
	// イージング用
	float easetime;
	uint32_t time;
	uint32_t easeMaxTime = 50;
	bool on = false;
public:
	//代入演算子削除
	TransitionsScene& operator=(const TransitionsScene&) = delete;

	//コピーコンストラクタ削除
	TransitionsScene(const TransitionsScene&) = delete;

};

