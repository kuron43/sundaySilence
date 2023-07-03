#include "SceneObjects.h"

SceneObjects::SceneObjects(DirectXCommon*DXCommon,Camera* camera) {
	_dxCommon = DXCommon;
	_camera = camera;
}
SceneObjects::~SceneObjects() {

}
void SceneObjects::Initialize() {

	audio = std::make_unique<Audio>();
	audio->Initialize();
	// fbx テスト
	{


		bossFbxM_.reset(FbxLoader::GetInstance()->LoadModelFromFile("boss_prot4"));
		bossFbxO_ = std::make_unique<FBXObject3d>();
		bossFbxO_->SetCamera(_camera);
		bossFbxO_->Initialize();
		bossFbxO_->SetModel(bossFbxM_.get());
		bossFbxO_->SetPosition({ 0,0,0 });
		bossFbxO_->SetScale({ 0.9f,0.9f,0.9f });
		bossFbxO_->PlayAnimation(1);
		bossFbxO_->AnimIsRotateChange();
	}

	{
		player = std::make_unique<Player>();
		player->Initialize();
	}
	{
		/*for (int i = 0; i <= 10; i++) {
			std::unique_ptr<Enemy>newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize();
			enemys.push_back(newEnemy);
		}*/
	}

	//ライトの生成
	lightGroup = std::make_unique< LightGroup>();
	lightGroup->Initialize();

	lightGroup->SetDirLightActive(0, true);
	pointLightPos[0] = 0.0f;
	pointLightPos[1] = 5.0f;
	pointLightPos[2] = 0.0f;

	lightGroup->SetDirLightColor(0, Vector3(1, 1, 1));
	lightGroup->SetDirLightDir(0, Vector4(1, -1, 0, 0));

	//3Dオブジェクトにライトをセット
	Object3d::SetLight(lightGroup.get());
}