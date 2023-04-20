#pragma once
#include "IScene.h"

class TitleScene :public IScene
{
protected:
	SceneManager* _controller;

public:
	
	TitleScene(SceneManager* controller);
	~TitleScene() override;

	void Initialize(DirectXCommon* dxCommon, Camera* _camera) override;
	void Update(Input* input, Camera* _camera) override;
	void Draw(DirectXCommon* dxCommon) override;
private:


public:
	

};