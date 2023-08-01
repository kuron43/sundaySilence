#pragma once
#include "IScene.h"

class PauseScene :
    public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	PauseScene(SceneManager* controller, SceneObjects* objects);
	~PauseScene() override;

	//void Cleate(SceneManager& controller) override;
	void Initialize() override;
	void Update(Input* input) override;
	void Draw() override;


private:

public:


};

