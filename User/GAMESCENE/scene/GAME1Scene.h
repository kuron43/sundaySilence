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
	void Initialize(DirectXCommon* dxCommon, Camera* _camera) override;
	void Update(Input* input, Camera* _camera) override;
	void Draw(DirectXCommon* dxCommon) override;

private:


public:
	Object3d* obj2 = nullptr;
	Model* obj2MD = nullptr;

	Object3d* obj3 = nullptr;
	Model* obj3MD = nullptr;

};

