#pragma once
#include "Scene.h"
class EndScene :
    public Scene
{
protected:
	SceneManager* _controller;

public:
	EndScene(SceneManager* controller);
	EndScene();
	~EndScene() override;

	//void Cleate(SceneManager& controller) override;
	void Initialize(DirectXCommon* dxCommon) override;
	void Update(Input* input) override;
	void Draw(DirectXCommon* dxCommon) override;


private:

public:


};