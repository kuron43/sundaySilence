#pragma once
#include "IScene.h"



class GAME1Scene :
    public IScene
{
protected:
	SceneManager* _controller;

public:
	GAME1Scene(SceneManager* controller);
	~GAME1Scene() override;

	//void Cleate(SceneManager& controller) override;
	void Initialize(DirectXCommon* dxCommon) override;
	void Update(Input* input) override;
	void Draw(DirectXCommon* dxCommon) override;

private:


public:
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;

};
