#include "Tutorial.h"

/**
 * @file Tutorial.cpp
 * @brief ゲーム実行 チュートリアルステージ
 */
#include "Tutorial.h"
#include "SceneManager.h"

Tutorial::Tutorial() {
}

Tutorial::~Tutorial() {
	BulletManager::GetInstance()->AllClearBullet();
	_objects->walls.clear();
	_objects->enemys.clear();
	_objects->boss.clear();
	_objects->damageRedAlpha_ = 0;
	_objects->player->Reset();
	_objects->SlowReset();
	_objects->plDamageRed_->SetColor(Vector4(1, 0, 0, _objects->damageRedAlpha_ / (float)_objects->player->GetMAXHP()));
	_objects->plDamageRed_->Update();
}

void Tutorial::Initialize() {
	_objects->SlowReset();
	_objects->player->Reset();
	_objects->player->MatUpdate();
	startTime_ = true;
	stageClear = false;
	stageFailed = false;
	SpriteInitialize();
	{

		_manager->_camera->SetEye(camposEye);
		_manager->_camera->SetTarget(camposTar);
		_manager->_camera->SetFocalLengs(forcalLengs);
		_manager->_camera->Update();
		camMoveTime_ = NUMBER::NUM_ZERO;

		_objects->floorGround->Update();

		BulletManager::GetInstance()->Update();
		for (std::unique_ptr <Enemy>& enemy : _objects->enemys) {
			enemy->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
			enemy->Update();
			if (!enemy->HowDead()) {
				_objects->eneCount++;
			}
		}
		for (std::unique_ptr <Boss>& boss : _objects->boss) {
			boss->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
			boss->Update();
			if (!boss->HowDead()) {
				_objects->bossCount++;
			}
		}
		for (std::unique_ptr < Wall>& walls : _objects->walls) {
			walls->Update();
		}
	}
}

void Tutorial::Update(Input* input) {
	_objects->eneCount = 0;
	_objects->bossCount = 0;
	_objects->floorGround->Update();
	//_objects->bossFbxO_->Update();
	if (input) {

	}
	_manager->_camera->SetEye(camposEye);
	_manager->_camera->SetTarget(camposTar);

#ifdef _DEBUG
	ImGui::Begin("Tutorial_S");
	ImGui::SliderFloat3("Position", &moveCameraPos.x,-50.0,50.0);
	ImGui::End();
#endif
	// {-47,0,-29}POS,{70}FL
	forcalLengs = 70.0f;

	Vector3 debugEyE = { 0.0f,90.0f,-10.0001f };
	Vector3 debugTar = { 0,0,0 };
		camposEye = debugEyE + moveCameraPos;
		camposTar = debugTar + moveCameraPos;
	if (startTime_ == true && stageClear == false && stageFailed == false) {
		startTime_ = _objects->Banner();
		camMoveTime_++;
	}
	else if (startTime_ == false && stageClear == false && stageFailed == false) {

		TutorialUpdate(_manager->tutorialNum);
	}
	else if (startTime_ == false && stageClear == false && stageFailed == true) {
		stageFailed = _objects->Banner(NUMBER::NUM_ONE);
		if (stageFailed == false) {
			_manager->SetSceneNum(SCE_GAME1);
		}
	}
	else if (startTime_ == false && stageClear == true && stageFailed == false) {
		stageClear = _objects->Banner(NUMBER::NUM_TWO);
		if (stageClear == false) {
			/*_manager->SetSceneNum(SCE_CLEAR);*/
			_manager->SetSceneNum(SCE_GAME1);
			if (_manager->tutorialNum == TUTO_3) {
				_manager->TutorialOFF();
				_manager->SetSceneNum(SCE_CLEAR);
			}
		}
	}
	_objects->UIUpdate();
}

void Tutorial::Draw() {
	_objects->floorGround->Draw(_manager->_dxCommon);
	for (std::unique_ptr <Enemy>& enemy : _objects->enemys) {
		enemy->Draw(_manager->_dxCommon);
	}
	for (std::unique_ptr <Boss>& boss : _objects->boss) {
		boss->Draw(_manager->_dxCommon);
	}
	for (std::unique_ptr <Wall>& walls : _objects->walls) {
		walls->Draw(_manager->_dxCommon);
	}
	//_objects->bossFbxO_->Draw(_manager->_dxCommon->GetCommandList());

	Object3d::PreDraw(_manager->_dxCommon->GetCommandList());

	BulletManager::GetInstance()->Draw();

	Object3d::PostDraw();
	if (startTime_ == false) {
		_objects->player->Draw(_manager->_dxCommon);
	}
	_objects->SlowEffectDraw();
	_objects->plDamageRed_->Draw();
	_objects->UIDraw();
	if (startTime_ == false && stageClear == false && stageFailed == false) {
		SpriteDraw(isDrawSP_);
	}
	if (startTime_ == true || stageFailed == true || stageClear == true) {
		_objects->BannerDraw();
	}
}

void Tutorial::TutorialUpdate(uint32_t tutorialNum)
{
#ifdef _DEBUG
	if (Input::get_instance().KeyboardPush(DIK_P)) {
		Vector3 eyeDebug = _objects->player->GetTransform().position;
		eyeDebug.y = (float)3.5f;
		_manager->_camera->SetEye(eyeDebug);
		_manager->_camera->SetTarget(_objects->player->GetReticleTransform().position);
		_manager->_camera->Update();
	}
#endif // DEBUG

	_objects->player->Update(&Input::get_instance());
	_objects->SlowEffect(_objects->player->GetIsSlow());
	_objects->damageRedAlpha_ = (float)_objects->player->GetHIT() / (float)_objects->player->GetMAXHP();
	_objects->plDamageRed_->SetColor(Vector4(1, 0, 0, _objects->damageRedAlpha_ / (float)_objects->player->GetMAXHP()));

	stageFailed = _objects->player->GetIsDeath();

	SpriteUpdate(tutorialNum);
	BulletManager::GetInstance()->Update();

	for (std::unique_ptr <Enemy>& enemy : _objects->enemys) {
		enemy->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
		enemy->Update();
		if (!enemy->HowDead()) {
			_objects->eneCount++;
		}
	}
	for (std::unique_ptr <Boss>& boss : _objects->boss) {
		boss->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
		boss->Update();
		if (!boss->HowDead()) {
			_objects->bossCount++;
		}
	}
	for (std::unique_ptr < Wall>& walls : _objects->walls) {
		walls->Update();
	}	

	if (Input::get_instance().KeyboardTrigger(DIK_TAB)) {
		_manager->SetSceneNum(SCE_PAUSE);
	}
	else if (_objects->eneCount == 0 && _objects->bossCount == 0) {
		stageClear = true;
		_manager->tutorialNum += 1;
	}
}

void Tutorial::SpriteInitialize()
{
	infoSP_ = std::make_unique<Sprite>();
	infoSP_->Initialize(_objects->spriteCommon_.get(), 60);
	infoSP_->SetSize({ 300,150 });
	infoSP_->SetPozition({ (WinApp::window_width / 1.5f) - 150,WinApp::window_height - 200 });
	isDrawSP_ = true;
	infoNum_ = 61;
	nowInfoNum_ = 0;

	isInfoBarrier = false;
	isInfoSHOT = false;
	isInfoSLOW = true;
	isInfoDUSH = false;
	isInfoWEPC = false;
	isAllFalse = true;
	isTimeCount = false;
	if (_manager->tutorialNum == TUTO_2) {
		infoNum_ = 62;
	}
}

void Tutorial::SpriteUpdate(uint32_t tutorialNum) {

	if (isTimeCount) {
		infoCountTime_++;
	}
	if (isInfoSLOW == true && infoCountTime_ > 150) {
		nowInfoNum_ = 1;
		isInfoSLOW = false;
		isTimeCount = false;
		infoCountTime_ = 0;
		isInfoDUSH = true;
	}else if (isInfoDUSH == true && infoCountTime_ > 150) {
		nowInfoNum_ = 1;
		isInfoDUSH = false;
		isTimeCount = false;
		infoCountTime_ = 0;
		isInfoSLOW = true;
	}
	else {

	}
	switch (tutorialNum)
	{
	case TUTO_1:
	//InfoBarrier
		infoNum_ = 60;	
	break;
	case TUTO_2:
	// InfoSlow&Dash
		isTimeCount = true;
	if (isInfoSLOW == true && infoCountTime_ >= 150) {
		infoNum_ = 62;
	}
	if (isInfoDUSH == true && infoCountTime_ >= 150) {
		infoNum_ = 63;
	}if (isInfoDUSH == false && isInfoSLOW == false|| isInfoDUSH == true && isInfoSLOW == true) {
		isInfoSLOW = true;
		isInfoDUSH = false;
	}
	break;
	case TUTO_3:
		infoNum_ = 64;
	break;
	default:
		break;
	}

	infoSP_->SetTextureIndex(infoNum_);
}

void Tutorial::SpriteDraw(bool isTutrial)
{
	if (isTutrial == true) {
		infoSP_->Draw();
	}
}
