#pragma once
#include "IScene.h"

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


public:
	

};