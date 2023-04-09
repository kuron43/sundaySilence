#pragma once
#include "IScene.h"

class TitleScene :public IScene
{
protected:
	SceneManager* _controller;

public:
	
	TitleScene(SceneManager* controller);
	~TitleScene() override;

	void Initialize(DirectXCommon* dxCommon) override;
	void Update(Input* input) override;
	void Draw(DirectXCommon* dxCommon) override;
private:


public:
	//パーティクルクラスの初期化 
	ParticleManager* particleManager = nullptr;
	ParticleManager* particleManager2 = nullptr;


	SpriteCommon* spriteCommon = nullptr;
	Sprite* sprite = nullptr;
	Sprite* sprite2 = nullptr;

	Object3d* obj = nullptr;
	Model* model = nullptr;

	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;

};