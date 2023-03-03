#pragma once
#include "Scene.h"

#include "Sprite.h"
#include "DirectXCommon.h"



class TitleScene :public Scene
{
protected:
	SceneManager* _controller;

public:
	
	TitleScene(SceneManager* controller);
	~TitleScene() override;

	//TitleScene Create(SceneManager& controller);
	void Initialize(DirectXCommon* dxCommon) override;
	void Update(Input* input) override;
	void Draw(DirectXCommon* dxCommon) override;


private:

public:
	SpriteCommon* spriteCommon = nullptr;
	Sprite* sprite = nullptr;


};