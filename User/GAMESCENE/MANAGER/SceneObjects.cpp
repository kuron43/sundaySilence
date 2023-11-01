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

	ShowCursor(false);
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
		spriteCommon_->LoadTexture(13, "readySTART.png");
		spriteCommon_->LoadTexture(14, "faildBuck.png");
		spriteCommon_->LoadTexture(15, "faildFAILED.png");
		spriteCommon_->LoadTexture(16, "clearBuck.png");
		spriteCommon_->LoadTexture(17, "clearCLEAR.png");
		spriteCommon_->LoadTexture(18, "Cursor2.png");

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
		plDamageRed_ = std::make_unique<Sprite>();
		plDamageRed_->Initialize(spriteCommon_.get(), 30);
		plDamageRed_->SetSize({ WinApp::window_width ,WinApp::window_height });
		plDamageRed_->SetPozition(plDamageRedPos);
		plDamageRed_->SetColor(Vector4(0, 0, 0, 0));
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
		bannerBuckSP_ = std::make_unique<Sprite>();
		bannerBuckSP_->Initialize(spriteCommon_.get(), 12);
		bannerBuckSP_->SetSize({ WinApp::window_width / 2.0f ,100.0f });
		bannerBuckSPpos_ = { 0,WinApp::window_height / 2.0f };
		bannerBuckSPscale_ = Vector3(1.0f, 0001.0f, 1.0f);
		bannerBuckSP_->SetPozition(bannerBuckSPpos_);
		bannerBuckSP_->SetScale(bannerBuckSPscale_);
	}
	{
		bannerBuck2SP_ = std::make_unique<Sprite>();
		bannerBuck2SP_->Initialize(spriteCommon_.get(), 12);
		bannerBuck2SP_->SetSize({ WinApp::window_width / 2.0f ,100.0f });
		bannerBuck2SPpos_ = { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f };
		bannerBuck2SPscale_ = Vector3(1.0f, 0.0001f, 1.0f);
		bannerBuck2SP_->SetPozition(bannerBuck2SPpos_);
		bannerBuck2SP_->SetScale(bannerBuck2SPscale_);
	}
	{
		bannerWordSP_ = std::make_unique<Sprite>();
		bannerWordSP_->Initialize(spriteCommon_.get(), 13);
		bannerWordSP_->SetSize({ 300.0f ,100.0f });
		bannerWordSPpos_ = { -300.0f, WinApp::window_height / 2.0f };
		bannerWordSPscale_ = Vector3(1.0f, 1.0f, 1.0f);
		bannerWordSP_->SetPozition(bannerWordSPpos_);
		bannerWordSP_->SetScale(bannerWordSPscale_);
	}
	{
		backWall = { 0,2,10,21,0,0, };
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

bool SceneObjects::Banner(uint32_t isStart)
{

	if (isStart == 0) {
		bannerBuckSP_->SetTextureIndex(12);
		bannerBuck2SP_->SetTextureIndex(12);
		bannerWordSP_->SetTextureIndex(13);
	}
	if(isStart == 1){
		bannerBuckSP_->SetTextureIndex(14);
		bannerBuck2SP_->SetTextureIndex(14);
		bannerWordSP_->SetTextureIndex(15);
	}
	if (isStart == 2) {
		bannerBuckSP_->SetTextureIndex(16);
		bannerBuck2SP_->SetTextureIndex(16);
		bannerWordSP_->SetTextureIndex(17);
	}

	bannerTimer++;
	time++;
	easetime = (float)time / easeMaxTime;
	if (isEaseOut) {
		bannerBuckSPscale_ = Easing::OutQuintVec3(Vector3(1.0f, 0.0001f, 1.0f), Vector3(1, 1, 1), (float)easetime);
		bannerBuckSPpos_ = Easing::OutQuintVec2(Vector2(0.0f, WinApp::window_height / 2.0f), Vector2(0.0f, WinApp::window_height / 2.0f), (float)easetime);
		bannerBuck2SPscale_ = Easing::OutQuintVec3(Vector3(1.0f, 0.0001f, 1.0f), Vector3(1, 1, 1), (float)easetime);
		bannerBuck2SPpos_ = Easing::OutQuintVec2(Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f), (float)easetime);
		bannerWordSPpos_ = Easing::OutQuintVec2(Vector2(-300.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width / 2.0f - 150.0f, WinApp::window_height / 2.0f), (float)easetime);
	}
	else {
		bannerBuckSPpos_ = Easing::InQuintVec2(Vector2(0.0f, WinApp::window_height / 2.0f), Vector2(-(WinApp::window_width / 2.0f), WinApp::window_height / 2.0f), (float)easetime);
		bannerBuck2SPpos_ = Easing::InQuintVec2(Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width, WinApp::window_height / 2.0f), (float)easetime);
		//readyStartSPpos_ = Easing::InQuintVec2(Vector2(WinApp::window_width / 2.0f - 150.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width / 2.0f - 150.0f, -100.0f), (float)easetime);
		bannerWordSP_->SetColor({ 1.0f,1.0f,1.0f,Easing::InQuintFloat(1.0f,0.0f, (float)easetime) });
	}
	bannerBuckSP_->SetScale(bannerBuckSPscale_);
	bannerBuckSP_->SetPozition(bannerBuckSPpos_);
	bannerBuck2SP_->SetScale(bannerBuck2SPscale_);
	bannerBuck2SP_->SetPozition(bannerBuck2SPpos_);
	bannerWordSP_->SetScale(bannerWordSPscale_);
	bannerWordSP_->SetPozition(bannerWordSPpos_);

	bannerBuckSP_->Update();
	bannerBuck2SP_->Update();
	bannerWordSP_->Update();


	if (time >= easeMaxTime && isEaseOut == true) {
		time = 0;
		easetime = 0;
		isEaseOut = false;
	}
	if (time >= easeMaxTime && isEaseOut == false) {
		time = 0;
		easetime = 0;
		isEaseOut = true;
		return false;
	}
	return true;
}
void SceneObjects::ShakeRand(Shake& shake)
{
	//フラグ0
	if (shake.isShake == 0) {
		shake.quantity = 23;
		shake.maxSwing = 10;
		shake.count = 50;
	}

	if (shake.isShake == 1) {
		shake.randX = rand() % shake.quantity - shake.maxSwing;
		shake.randZ = rand() % shake.quantity - shake.maxSwing;
		shake.count--;
	}

}
void SceneObjects::BannerDraw()
{
	bannerBuckSP_->Draw();
	bannerBuck2SP_->Draw();
	bannerWordSP_->Draw();
}
