#pragma once
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Audio.h"
#include "SceneManager.h"
#include "ParticleManager.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Camera.h"

class SceneManager;

// シーン管理のための基底クラス
// (純粋基底クラス)

class IScene
{
protected:

	SceneManager* _controller;

public:

	IScene();
	virtual ~IScene();

	//virtual Scene Create(SceneManager& controller) = 0;
	/// シーンの更新を行う
	virtual void Initialize(DirectXCommon* dxCommon,Camera* _camera) = 0;

	/// シーンの更新を行う
	virtual void Update(Input* input, Camera* _camera) = 0;

	/// シーンの描画を行う
	virtual void Draw(DirectXCommon* dxCommon) = 0;

};

