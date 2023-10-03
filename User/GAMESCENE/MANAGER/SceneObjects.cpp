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
	{
		//スプライト初期化
		spriteCommon_ = std::make_unique<SpriteCommon>();
		spriteCommon_->Initialize(_dxCommon);
		// TITLE
		spriteCommon_->LoadTexture(1, "title.png");
		spriteCommon_->LoadTexture(2, "inu.png");
		spriteCommon_->LoadTexture(3, "end.png");
		spriteCommon_->LoadTexture(4, "clear.png");
		spriteCommon_->LoadTexture(5, "select.png");
		spriteCommon_->LoadTexture(6, "gray.png");
		//spriteCommon_->LoadTexture(7, "Cursor.png");
		spriteCommon_->LoadTexture(7, "mouse.png");


		spriteCommon_->LoadTexture(16, "1.png");
		spriteCommon_->LoadTexture(17, "2.png");
		spriteCommon_->LoadTexture(18, "3.png");
	}

	mouseCursor_ = std::make_unique<Cursor>();
	mouseCursor_->Initialize(spriteCommon_.get());

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
		wallMD = Model::LoadFromOBJ("wall");
	}
	skydome_O = std::make_unique<Object3d>();
	skydome_O->SetModel(Model::LoadFromOBJ("skydome"));
	skydome_O->Initialize();
	skydome_O->wtf.scale = Vector3(1000.0f, 1000.0f, 1000.0f);
	//ライトの生成
	lightGroup = std::make_unique< LightGroup>();
	lightGroup->Initialize();

	lightGroup->SetDirLightActive(0, true);
	pointLightPos[0] = 0.0f;
	pointLightPos[1] = 5.0f;
	pointLightPos[2] = 0.0f;

	lightGroup->SetDirLightColor(0, Vector3(1, 1, 1));
	lightGroup->SetDirLightDir(0, Vector4(0, 0, 0, 0));

	//3Dオブジェクトにライトをセット
	Object3d::SetLight(lightGroup.get());
}