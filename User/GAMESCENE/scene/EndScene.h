#pragma once
#include "IScene.h"
#include "SceneIntegrate.h"

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
	std::unique_ptr <Sprite> end_;
public:

};