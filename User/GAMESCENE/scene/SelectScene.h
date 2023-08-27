#pragma once
#include "IScene.h"
#include "SceneIntegrate.h"

class SelectScene :
    public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	SelectScene(SceneManager* controller, SceneObjects* objects);
	~SelectScene() override;

	//void Cleate(SceneManager& controller) override;
	void Initialize() override;
	void Update(Input* input) override;
	void Draw() override;

	void SelectSceneNum(Input* input);
	void MoveScene();

private:
	std::unique_ptr <Sprite> titele_;
	std::unique_ptr <Sprite> stage1_;
	std::unique_ptr <Sprite> stage2_;

	int selectNum;
	int resultNum;
	bool isConfirm = false;

public:

};

