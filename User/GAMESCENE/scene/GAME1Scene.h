#pragma once
#include "IScene.h"



class GAME1Scene :
    public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	GAME1Scene(SceneManager* controller, SceneObjects* objects);
	~GAME1Scene() override;

	//void Cleate(SceneManager& controller) override;
	void Initialize() override;
	void Update(Input* input) override;
	void Draw() override;

private:


public:

};

