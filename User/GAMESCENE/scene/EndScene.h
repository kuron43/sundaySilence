#pragma once
#include "IScene.h"


class EndScene :
    public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	EndScene(SceneManager* controller, SceneObjects* objects);
	~EndScene() override;

	//void Cleate(SceneManager& controller) override;
	void Initialize() override;
	void Update(Input* input) override;
	void Draw() override;


private:

public:

};