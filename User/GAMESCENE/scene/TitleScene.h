#pragma once
#include "Scene.h"

class TitleScene :public Scene
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
	SpriteCommon* spriteCommon = nullptr;
	Sprite* sprite = nullptr;


};