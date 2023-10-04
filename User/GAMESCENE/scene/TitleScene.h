#pragma once
#include "IScene.h"
#include "SceneIntegrate.h"

class TitleScene :public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	
	TitleScene(SceneManager* controller, SceneObjects* objects);
	~TitleScene() override;

	void Initialize() override;
	void Update(Input* input) override;
	void Draw() override;
private:
	Vector3 camposEye = { 0.0f,0.0f,-100.01f };
	Vector3 camposTar = { 0,0,0 };

public:
	
private://リソース
	std::unique_ptr <Sprite> title_;
	std::unique_ptr <Sprite> titleButton_;
};