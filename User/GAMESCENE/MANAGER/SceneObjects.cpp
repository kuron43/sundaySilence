/**
 * @file SceneObject.cpp
 * @brief シーンオブジェクト所持クラス
 */
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
		spriteCommon_->LoadTexture(10, "BACK.png");
		spriteCommon_->LoadTexture(11, "title2.png");
		spriteCommon_->LoadTexture(12, "readyBuck.png");

	}
	// スプライトロード  20~ //セレクトステージ
	{
		spriteCommon_->LoadTexture(20, "1.png");
		spriteCommon_->LoadTexture(21, "2.png");
		spriteCommon_->LoadTexture(22, "3.png");
		spriteCommon_->LoadTexture(26, "Left.png");
		spriteCommon_->LoadTexture(27, "Left2.png");
		spriteCommon_->LoadTexture(28, "Right.png");
		spriteCommon_->LoadTexture(29, "Right2.png");
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


	// 演出用の初期化
	{
		readyBuckSP_ = std::make_unique<Sprite>();
		readyBuckSP_->Initialize(spriteCommon_.get(), 12);
		readyBuckSP_->SetSize({ WinApp::window_width / 2.0f ,100.0f });
		readyBuckSPpos_ = { 0,WinApp::window_height / 2.0f };
		readyBuckSPscale_ = Vector3(1.0f, 0001.0f, 1.0f);
		readyBuckSP_->SetPozition(readyBuckSPpos_);
		readyBuckSP_->SetScale(readyBuckSPscale_);
	}
	{
		readyBuck2SP_ = std::make_unique<Sprite>();
		readyBuck2SP_->Initialize(spriteCommon_.get(), 12);
		readyBuck2SP_->SetSize({ WinApp::window_width / 2.0f ,100.0f });
		readyBuck2SPpos_ = { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f };
		readyBuck2SPscale_ = Vector3(1.0f, 0.0001f, 1.0f);
		readyBuck2SP_->SetPozition(readyBuck2SPpos_);
		readyBuck2SP_->SetScale(readyBuck2SPscale_);
	}


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

bool SceneObjects::Ready()
{

	readyTimer++;
	time++;
	easetime = (float)time / easeMaxTime;
	if (isEaseOut) {
		readyBuckSPscale_ = Easing::OutQuintVec3(Vector3(1.0f, 0.0001f, 1.0f), Vector3(1, 1, 1), (float)easetime);
		readyBuckSPpos_ = Easing::OutQuintVec2(Vector2(0.0f, WinApp::window_height / 2.0f), Vector2(0.0f, WinApp::window_height / 2.0f + 50.0f), (float)easetime);
		readyBuck2SPscale_ = Easing::OutQuintVec3(Vector3(1.0f, 0.0001f, 1.0f), Vector3(1, 1, 1), (float)easetime);
		readyBuck2SPpos_ = Easing::OutQuintVec2(Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f + 50.0f), (float)easetime);
	}
	else {
		readyBuckSPpos_ = Easing::InQuintVec2(Vector2(0.0f, WinApp::window_height / 2.0f + 50.0f), Vector2(-(WinApp::window_width / 2.0f), WinApp::window_height / 2.0f + 50.0f), (float)easetime);
		readyBuck2SPpos_ = Easing::InQuintVec2(Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f + 50.0f), Vector2(WinApp::window_width, WinApp::window_height / 2.0f + 50.0f), (float)easetime);
	}
	readyBuckSP_->SetScale(readyBuckSPscale_);
	readyBuckSP_->SetPozition(readyBuckSPpos_);
	readyBuck2SP_->SetScale(readyBuck2SPscale_);
	readyBuck2SP_->SetPozition(readyBuck2SPpos_);

	readyBuckSP_->Update();
	readyBuck2SP_->Update();

	if (time >= easeMaxTime && isEaseOut == true) {
		time = 0;
		isEaseOut = false;
	}
	if (time >= easeMaxTime && isEaseOut == false) {
		time = 0;
		isEaseOut = true;
		return false;
	}
	return true;
}
void SceneObjects::ReadyDraw()
{
	readyBuckSP_->Draw();
	readyBuck2SP_->Draw();
}
