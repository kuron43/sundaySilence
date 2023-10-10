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

	//void Cleate(SceneManager& controller) override;
	void Initialize() override;
	void Update(Input* input) override;
	void Draw() override;


private:
	std::unique_ptr <Sprite> transSP_;

	// イージング用
	uint32_t time;
	float easetime;
	uint32_t easeMaxTime = 30;
public:
	//代入演算子削除
	TransitionsScene& operator=(const TransitionsScene&) = delete;

	//コピーコンストラクタ削除
	TransitionsScene(const TransitionsScene&) = delete;

};

