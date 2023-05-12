#include "SceneManager.h"
#include "Input.h"
#include <cassert>
#include "DirectXCommon.h"
#include "Camera.h"

// シーンのインクルード
#include "SceneIntegrate.h"


SceneManager::SceneManager(DirectXCommon* dxCommon, Camera* camera) {
	_dxCommon = dxCommon;
	_scene.reset(new TitleScene(&*this));
	_camera = camera;


}
SceneManager::~SceneManager() {

}
void SceneManager::ObjectInitialize() {

	//スプライト初期化
	//spriteCommon_ = std::make_unique<SpriteCommon>();
	//spriteCommon_->Initialize(_dxCommon);
	//spriteCommon_->LoadTexture(1, "gamen.png");
	//spriteCommon_->LoadTexture(2, "title.png");

	audio = std::make_unique<Audio>();
	audio->Initialize();
	// fbx テスト
	{
		//FBX	(テスト)
		// デバイスをセット
		FBXObject3d::SetDevice(_dxCommon->GetDevice());
		// グラフィックスパイプライン生成
		FBXObject3d::CreateGraphicsPipeline();

		bossFbxM_.reset(FbxLoader::GetInstance()->LoadModelFromFile("boss_prot4"));
		bossFbxO_ = std::make_unique<FBXObject3d>();
		bossFbxO_->SetCamera(_camera);
		bossFbxO_->Initialize();
		bossFbxO_->SetModel(bossFbxM_.get());
		bossFbxO_->SetPosition({ 0,0,0 });
		bossFbxO_->SetScale({ 1,1,1 });
		bossFbxO_->PlayAnimation(1);
		bossFbxO_->AnimIsRotateChange();
	}
	
	////パーティクルのセット
	//particleManager_ = std::make_unique<ParticleManager>();
	//particleManager_.get()->Initialize();
	////パーティクル用素材
	//particleManager_->LoadTexture("effect.png");
	//particleManager_->Update();
	
	//ライトの生成
	lightGroup = std::make_unique< LightGroup>();
	lightGroup->Initialize();

	//lightGroup->SetDirLightActive(0, true);
	//lightGroup->SetDirLightActive(1, true);
	//lightGroup->SetDirLightActive(2, true);

	lightGroup->SetDirLightActive(0, true);
	/*lightGroup->SetDirLightActive(1, false);
	lightGroup->SetDirLightActive(2, false);
	lightGroup->SetPointLightActive(0, true);*/
	pointLightPos[0] = 0.0f;
	pointLightPos[1] = 5.0f;
	pointLightPos[2] = 0.0f;

		lightGroup->SetDirLightColor(0, Vector3(1, 1, 1));
		lightGroup->SetDirLightDir(0, Vector4(1, -1, 0, 0));
	/*lightGroup->SetCircleShadowActive(0, true);*/

	//3Dオブジェクトにライトをセット
	Object3d::SetLight(lightGroup.get());
}

void SceneManager::SceneInitialize() {
	_scene.get()->Initialize(_dxCommon, _camera);

}

void SceneManager::SceneUpdate(Input* input) {
	lightGroup->Update();
	{
		/*
		lightGroup->SetPointLightPos(0, XMFLOAT3(pointLightPos));
		lightGroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
		lightGroup->SetPointLightAtten(0, XMFLOAT3(pointLightAtten));
		*/
	}
	_scene.get()->Update(input, _camera);
}

void SceneManager::SceneDraw() {
	_scene.get()->Draw(_dxCommon);

}

void SceneManager::ChangeScene(IScene* scene) {
	_scene.reset(scene);
	SceneInitialize();

}