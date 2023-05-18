#pragma once
#include <memory>
#include <stack>

#include "LightGroup.h"

#include "FBXObject3d.h"
#include "fbx/FBXLoader.h"
#include "FBXModel.h"
#include "Audio.h"
#include "SpriteCommon.h"
#include "Model.h"
#include "Object3d.h"
#include "ParticleManager.h"


class Input;
class IScene;
class DirectXCommon;
class Camera;

// シーン管理クラス
class SceneManager
{
private:
	std::shared_ptr<IScene> _scene;
	DirectXCommon* _dxCommon;
	Camera* _camera;
	
public:



	SceneManager(DirectXCommon* dxCommon, Camera* camera);
	~SceneManager();

	//オブジェクトのInitializeを呼び出す
	void ObjectInitialize();
	// 各シーンのInitializeを呼び出す
	void SceneInitialize();
	// 各シーンのUpdateを呼び出す
	void SceneUpdate(Input* input);
	// 各シーンのDrawを呼び出す
	void SceneDraw();

	// シーンを変更する
	void ChangeScene(IScene*);
	//ID3D12GraphicsCommandList* GetCommandList() { return _dxCommon->GetCommandList(); };
public:
	std::unique_ptr <LightGroup> lightGroup;
	std::unique_ptr <Audio> audio;
	std::unique_ptr <SpriteCommon> spriteCommon_;

	std::unique_ptr<ParticleManager> particleManager_;
	std::unique_ptr<ParticleManager> particleManager2_;

	std::unique_ptr <Object3d> object3d;
	std::unique_ptr <Model> model;

	//FBXモデル
	std::unique_ptr<FBXModel> bossFbxM_;
	std::unique_ptr<FBXObject3d> bossFbxO_;


private:
	float ambientColor0[3] = { 1,1,1 };

	//光線方向初期値
	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,1,1 };
	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 1,1,1 };
	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 1,1,1 };

	float pointLightPos[3] = { 0,4,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.3f,0.1f,0.1f };

	float spotLightDir[3] = { 0,-1,0 };
	float spotLightPos[3] = { 0,5,0 };
	float spotLightColor[3] = { 1,1,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 20.0f,30.0f };

	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f,0.5f };
};

//	参照元
//	https://qiita.com/tsuchinokoman/items/390a22a20abe2a6daa6d <-やり方わからん