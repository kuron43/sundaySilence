#pragma once
#include "IScene.h"


class EndScene :
    public IScene
{
protected:
	SceneManager* _controller;

public:
	EndScene(SceneManager* controller);
	~EndScene() override;

	//void Cleate(SceneManager& controller) override;
	void Initialize(DirectXCommon* dxCommon) override;
	void Update(Input* input) override;
	void Draw(DirectXCommon* dxCommon) override;


private:

public:

};