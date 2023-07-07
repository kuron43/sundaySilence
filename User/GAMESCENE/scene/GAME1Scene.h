#pragma once
#include "IScene.h"

#include "JsonLoader.h"


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
	bool stageClear = false;
	bool stageFailed = false;

	// カメラ座標
	Vector3 camposEye = { 0.0f,100.0f,-10.0f };
	Vector3 camposTar = { 0,0,0 };

public:


	// json
	Model* modelcube = nullptr;
	//Model* modelREX = nullptr;

	LevelData* leveData = nullptr;
	std::map<std::string, Model*> jsonModels;
	std::vector<Object3d*> JsonObjects;

};

