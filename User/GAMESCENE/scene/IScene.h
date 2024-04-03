#pragma once
/**
 * @file IScene.h
 * @brief
 */
#include "SceneManager.h"
#include "SceneObjects.h"
#include "ParticleManager.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Camera.h"
#include "Sprite.h"

#pragma warning(push)
#pragma warning(disable: 4514)
#include <imgui.h>
#include <random>
#pragma warning(pop)

class SceneManager;

// シーン管理のための基底クラス
// (純粋基底クラス)

class IScene
{
protected:

	static SceneManager* _manager;
	static SceneObjects* _objects;

public:

	IScene();
	virtual ~IScene();

	//virtual Scene Create(SceneManager& manager) = 0;
	/// シーンの初期化を行う
	virtual void Initialize() = 0;

	/// シーンの更新を行う
	virtual void Update(Input* input) = 0;

	/// シーンの描画を行う
	virtual void Draw() = 0;

	static void SetSceneManager(SceneManager* manager) { _manager = manager; };
	static void SetSceneObjects(SceneObjects* objects) { _objects = objects; };

};

