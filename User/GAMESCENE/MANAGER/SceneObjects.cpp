#include "SceneObjects.h"

SceneObjects::SceneObjects(DirectXCommon* DXCommon, Camera* camera) {
	_dxCommon = DXCommon;
	_camera = camera;
}
SceneObjects::~SceneObjects() {

}
void SceneObjects::Initialize() {


	audio = std::make_unique<Audio>();
	audio->Initialize();
	{
		enum spriteNum
		{
			title = 1,
			inu = 2,
			end = 3,
			clear = 4,
			select = 5,
			gray = 6,
			Cursor = 7,
			START = 8,
			START2 = 9,
		};
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
		spriteCommon_->LoadTexture(7, "Cursor.png");
		spriteCommon_->LoadTexture(8, "START.png");
		spriteCommon_->LoadTexture(9, "START2.png");
		spriteCommon_->LoadTexture(10,"BACK.png");
		spriteCommon_->LoadTexture(11, "title2.png");

	}
	// スプライトロード  20~ //セレクトステージ
	{
		spriteCommon_->LoadTexture(20, "1.png");
		spriteCommon_->LoadTexture(21, "2.png");
		spriteCommon_->LoadTexture(22, "3.png");
	}
	// スプライトロード  30~ //一時的な画像用
	{
		spriteCommon_->LoadTexture(30, "red.png");
		spriteCommon_->LoadTexture(31, "orange.png");
		spriteCommon_->LoadTexture(32, "purple.png");
		spriteCommon_->LoadTexture(33, "yellow.png");
		spriteCommon_->LoadTexture(34, "black.png");
		spriteCommon_->LoadTexture(35, "white1x1.png");
		spriteCommon_->LoadTexture(36, "lightgray.png");
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
		floorGroundMD = Model::LoadFromOBJ("floor");
		floorGround = std::make_unique<Floor>();
		floorGround->Initialize(floorGroundMD);
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

void SceneObjects::Reset()
{
	enemys.clear();
	boss.clear();
	walls.clear();
}
