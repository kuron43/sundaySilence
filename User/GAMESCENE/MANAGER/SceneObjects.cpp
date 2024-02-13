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
	delete wallMD;
	delete floorGroundMD;
}
void SceneObjects::Initialize() {
	ShowCursor(false);
#ifdef _DEBUG
	ShowCursor(true);
#endif
	audio = std::make_unique<Audio>();
	audio->Initialize();
	// スプライトロード集
	{
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
			spriteCommon_->LoadTexture(21, "1_1.png");
			spriteCommon_->LoadTexture(22, "2.png");
			spriteCommon_->LoadTexture(23, "2_1.png");
			spriteCommon_->LoadTexture(24, "3.png");
			spriteCommon_->LoadTexture(25, "3_1.png");
			spriteCommon_->LoadTexture(26, "Left.png");
			spriteCommon_->LoadTexture(27, "Left2.png");
			spriteCommon_->LoadTexture(28, "Right.png");
			spriteCommon_->LoadTexture(29, "Right2.png");
		}
		// スプライトロード  30~ // 色画像用
		{
			spriteCommon_->LoadTexture(30, "red.png");
			spriteCommon_->LoadTexture(31, "orange.png");
			spriteCommon_->LoadTexture(32, "purple.png");
			spriteCommon_->LoadTexture(33, "yellow.png");
			spriteCommon_->LoadTexture(34, "black.png");
			spriteCommon_->LoadTexture(35, "white1x1.png");
			spriteCommon_->LoadTexture(36, "lightgray.png");
			spriteCommon_->LoadTexture(37, "cian.png");
			spriteCommon_->LoadTexture(38, "green.png");
		}
		// スプライトロード  40~ // UI画像用
		{
			spriteCommon_->LoadTexture(40, "UIbase.png");
			spriteCommon_->LoadTexture(41, "Weapon1ICON.png");
			spriteCommon_->LoadTexture(42, "Weapon2ICON.png");
			spriteCommon_->LoadTexture(43, "Weapon3ICON.png");
			spriteCommon_->LoadTexture(44, "Slow1ICON.png");
			spriteCommon_->LoadTexture(45, "Slow2ICON.png");
			spriteCommon_->LoadTexture(46, "Point1ICON.png");
			spriteCommon_->LoadTexture(47, "Point2ICON.png");
			spriteCommon_->LoadTexture(48, "pauseInfo.png");
		}
		// スプライトロード  50~ // シーン用
		{
			spriteCommon_->LoadTexture(50, "goTitle.png");
			spriteCommon_->LoadTexture(51, "goTitle2.png");
			spriteCommon_->LoadTexture(52, "pauseGoBack.png");
			spriteCommon_->LoadTexture(53, "GoSelect.png");
			spriteCommon_->LoadTexture(54, "GoSelect2.png");
			spriteCommon_->LoadTexture(55, "NEXT.png");
			spriteCommon_->LoadTexture(56, "NEXT2.png");

		}
		// スプライトロード  60~ // シーン用
		{
			spriteCommon_->LoadTexture(60, "TYU_WASD.png");
			spriteCommon_->LoadTexture(61, "TYU_SHOT.png");
			spriteCommon_->LoadTexture(62, "TYU_SLOW.png");
			spriteCommon_->LoadTexture(63, "TYU_DASH.png");
			spriteCommon_->LoadTexture(64, "TYU_WPCH.png");
			//spriteCommon_->LoadTexture(65, "NEXT.png");
			//spriteCommon_->LoadTexture(66, "NEXT2.png");

		}
	}

	mouseCursor_ = std::make_unique<Cursor>();
	mouseCursor_->Initialize(spriteCommon_.get());

	// fbx テスト
	{
		bossFbxM_.reset(FbxLoader::GetInstance()->LoadModelFromFile("Fbx_Rex"));
		bossFbxO_ = std::make_unique<FBXObject3d>();
		//bossFbxO_->SetCamera(_camera);
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
		floorGroundMD = Model::LoadFromOBJ("stage");
		floorGround = std::make_unique<Floor>();
		floorGround->Initialize(floorGroundMD);
	}
	skydome_O = std::make_unique<Object3d>();
	skydome_M = Model::LoadFromOBJ("skydome");
	skydome_O->SetModel(skydome_M);
	skydome_O->Initialize();
	skydome_O->wtf.scale = Vector3(10000.0f, 10000.0f, 10000.0f);


	// 演出用の初期化
	// バナー
	{

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
}
	// スロー
	{
		slowSP_ = std::make_unique<Sprite>();
		slowSP_->Initialize(spriteCommon_.get(), 32);
		slowSP_->SetPozition(Vector2{ 0.0f,0.0f });
		slowSP_->SetSize({ WinApp::window_width ,WinApp::window_height });
		slowSP_->SetColor(Vector4{ 0.1f,0.1f,0.1f,0.0f });
	}
	// UI
	{
		{
			UIBuckSP_ = std::make_unique<Sprite>();
			UIBuckSP_->Initialize(spriteCommon_.get(), 40);
			UIBuckSPpos_ = Vector2();
			UIBuckSPsize_ = Vector2{ WinApp::window_width ,WinApp::window_height };
			UIBuckSP_->SetPozition(UIBuckSPpos_);
			UIBuckSP_->SetSize(UIBuckSPsize_);
		}
		{
			UIWeaponSP_ = std::make_unique<Sprite>();
			UIWeaponSP_->Initialize(spriteCommon_.get(), 41);
			UIWeaponSPpos_ = Vector2{ WinApp::window_width - WinApp::window_width / 9.0f ,WinApp::window_height / 9.0f };
			UIWeaponSPsize_ = Vector2{ 80.0f ,80.0f };
			UIWeaponSP_->SetPozition(UIWeaponSPpos_);
			UIWeaponSP_->SetSize(UIWeaponSPsize_);
		}
		{
			UISlowSP_ = std::make_unique<Sprite>();
			UISlowSP_->Initialize(spriteCommon_.get(), 44);
			UISlowSPpos_ = Vector2{ UIWeaponSPpos_.x  ,UIWeaponSPpos_.y + 100.0f };
			UISlowSPsize_ = Vector2{ 80.0f ,80.0f };
			UISlowSP_->SetPozition(UISlowSPpos_);
			UISlowSP_->SetSize(UISlowSPsize_);
		}
		{
			UIPointSP_ = std::make_unique<Sprite>();
			UIPointSP_->Initialize(spriteCommon_.get(), 46);
			UIPointSPpos_ = Vector2{ UISlowSPpos_.x ,UISlowSPpos_.y + 100.0f};
			UIPointSPsize_ = Vector2{ 80.0f ,80.0f };
			UIPointSP_->SetPozition(UIPointSPpos_);
			UIPointSP_->SetSize(UIPointSPsize_);
		}
		{
			UIHPSP_ = std::make_unique<Sprite>();
			UIHPSP_->Initialize(spriteCommon_.get(), 38);
			UIHPSPpos_ = Vector2{ UIWeaponSPpos_.x + 26.0f ,WinApp::window_height - WinApp::window_height / 7.0f };
			UIHPSPsize_ = Vector2{30.0f,8.0f * player->GetHP()  };
			UIHPSP_->SetPozition(UIHPSPpos_);
			UIHPSP_->SetSize(UIHPSPsize_);
			UIHPSP_->SetIsFlipY(true);
		}
		{
			UIHPBaseSP_ = std::make_unique<Sprite>();
			UIHPBaseSP_->Initialize(spriteCommon_.get(), 30);
			UIHPBaseSPpos_ = Vector2{ UIWeaponSPpos_.x + 26.0f,WinApp::window_height - WinApp::window_height / 7.0f };
			UIHPBaseSPsize_ = Vector2{ 30.0f,8.0f * player->GetHP() };
			UIHPBaseSP_->SetPozition(UIHPBaseSPpos_);
			UIHPBaseSP_->SetSize(UIHPBaseSPsize_);
			UIHPBaseSP_->SetIsFlipY(true);
		}
		{
			backWall = { 0,2,10,21,0,0, };
		}
		{
			UIPauseSP_ = std::make_unique<Sprite>();
			UIPauseSP_->Initialize(spriteCommon_.get(), 48);
			UIPauseSPpos_ = Vector2{ 20 ,20 };
			UIPauseSPsize_ = Vector2{ 125.0f,64.0f };
			UIPauseSP_->SetPozition(UIPauseSPpos_);
			UIPauseSP_->SetSize(UIPauseSPsize_);
		}
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
	if (isStart == 1) {
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
	bannerTime++;
	bannerEasetime = (float)bannerTime / bannerEaseMaxTime;
	if (isBannerEaseOut) {
		bannerBuckSPscale_ = Easing::OutQuintVec3(Vector3(1.0f, 0.0001f, 1.0f), Vector3(1, 1, 1), (float)bannerEasetime);
		bannerBuckSPpos_ = Easing::OutQuintVec2(Vector2(0.0f, WinApp::window_height / 2.0f), Vector2(0.0f, WinApp::window_height / 2.0f), (float)bannerEasetime);
		bannerBuck2SPscale_ = Easing::OutQuintVec3(Vector3(1.0f, 0.0001f, 1.0f), Vector3(1, 1, 1), (float)bannerEasetime);
		bannerBuck2SPpos_ = Easing::OutQuintVec2(Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f), (float)bannerEasetime);
		bannerWordSPpos_ = Easing::OutQuintVec2(Vector2(-300.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width / 2.0f - 150.0f, WinApp::window_height / 2.0f), (float)bannerEasetime);
	}
	else {
		bannerBuckSPpos_ = Easing::InQuintVec2(Vector2(0.0f, WinApp::window_height / 2.0f), Vector2(-(WinApp::window_width / 2.0f), WinApp::window_height / 2.0f), (float)bannerEasetime);
		bannerBuck2SPpos_ = Easing::InQuintVec2(Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width, WinApp::window_height / 2.0f), (float)bannerEasetime);
		//readyStartSPpos_ = Easing::InQuintVec2(Vector2(WinApp::window_width / 2.0f - 150.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width / 2.0f - 150.0f, -100.0f), (float)easetime);
		bannerWordSP_->SetColor({ 1.0f,1.0f,1.0f,Easing::InQuintFloat(1.0f,0.0f, (float)bannerEasetime) });
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


	if (bannerTime >= bannerEaseMaxTime && isBannerEaseOut == true) {
		bannerTime = 0;
		bannerEasetime = 0;
		isBannerEaseOut = false;
	}
	if (bannerTime >= bannerEaseMaxTime && isBannerEaseOut == false) {
		bannerTime = 0;
		bannerEasetime = 0;
		isBannerEaseOut = true;
		return false;
	}
	return true;
}
void SceneObjects::BannerDraw()
{
	bannerBuckSP_->Draw();
	bannerBuck2SP_->Draw();
	bannerWordSP_->Draw();
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
void SceneObjects::SlowEffect(bool isSlow)
{
	if (isSlowEaseOut == true && slowPlayEase_ == true) {
		nowSlowEffect = true;
		slowTime++;
		slowEasetime = (float)slowTime / slowEaseMaxTime;
		slowSPAlpha_ = Easing::OutQuintFloat(slowSP_ALPHA_MIN, slowSP_ALPHA_MAX, (float)slowEasetime);
		if (slowSPAlpha_ == slowSP_ALPHA_MAX) {
			slowSPTime_MAX = true;
			nowSlowEffect = false;
			slowTime = 0;
			slowEasetime = 0;
		}
	}
	if (isSlowEaseOut == false && slowPlayEase_ == true) {
		nowSlowEffect = true;
		slowTime++;
		slowEasetime = (float)slowTime / slowEaseMaxTime;
		slowSPAlpha_ = Easing::OutQuintFloat(slowSP_ALPHA_MAX, slowSP_ALPHA_MIN, (float)slowEasetime);
		if (slowSPAlpha_ == slowSP_ALPHA_MIN) {
			slowSPTime_MAX = true;
			nowSlowEffect = false;
			slowTime = 0;
			slowEasetime = 0;
		}
	}

	if (isSlowEaseOut != isSlow && changeIsSlow == false) {
		changeIsSlow = true;
	}
	else {
		changeIsSlow = false;
	}
	if (nowSlowEffect == false && slowSPTime_MAX == true) {
		slowPlayEase_ = false;
	}
	if (changeIsSlow == true && slowPlayEase_ == false) {
		slowTime = 0;
		slowEasetime = 0;
		slowPlayEase_ = true;
		isSlowEaseOut = isSlow;
	}

	slowSP_->SetColorAlpha(slowSPAlpha_);
	slowSP_->Update();
}
void SceneObjects::SlowReset()
{
	slowSPAlpha_ = 0.0f;
	slowSPTime_MAX = false;
	slowPlayEase_ = false;
	nowSlowEffect = false;
	changeIsSlow = false;
	isSlowEaseOut = false;
	slowEasetime = 0.0f;
	slowTime = 0;
	slowSP_->SetColorAlpha(0.0f);
	slowSP_->Update();
}
void SceneObjects::SlowEffectDraw()
{
	slowSP_->Draw();
}

void SceneObjects::UIUpdate()
{
	if (player->GetOnFire()) {
		UIWeaponSP_->SetTextureIndex(42);
	}
	else {
		UIWeaponSP_->SetTextureIndex(41);
		UIPointSP_->SetTextureIndex(46);
	}
	if (player->GetIsSlow()) {
		UIWeaponSP_->SetTextureIndex(43);
		UISlowSP_->SetTextureIndex(45);
		UIPointSP_->SetTextureIndex(47);
		if (player->GetPointMAX()) {
			UIPointSP_->SetTextureIndex(46);
		}
	}
	else {
		UISlowSP_->SetTextureIndex(44);
	}
	ImGui::Begin("SpritePos");
	ImGui::InputFloat2("PAUSE TAB POS", &UIPauseSPpos_.x);
	ImGui::End();

	UIHPSPsize_.y = 8.0f * player->GetHP();
	UIHPSP_->SetSize(UIHPSPsize_);
	UIBuckSP_->Update();
	UIWeaponSP_->Update();
	UISlowSP_->Update();
	UIPointSP_->Update();
	UIHPSP_->Update();
	UIHPBaseSP_->Update();
	UIPauseSP_->Update();
}

void SceneObjects::UIDraw()
{
	//UIBuckSP_->Draw();
	UIWeaponSP_->Draw();
	UISlowSP_->Draw();
	UIPointSP_->Draw();
	UIHPBaseSP_->Draw();
	UIHPSP_->Draw();
	UIPauseSP_->Draw();
}
