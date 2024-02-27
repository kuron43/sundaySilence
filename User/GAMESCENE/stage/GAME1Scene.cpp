/**
 * @file GAME1Scene.cpp
 * @brief ゲーム実行１ステージ目
 */
#include "GAME1Scene.h"
#include "SceneManager.h"

GAME1Scene::GAME1Scene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}

GAME1Scene::~GAME1Scene() {
	BulletManager::GetInstance()->AllClearBullet();
	_objects->walls.clear();
	_objects->enemys.clear();
	_objects->boss.clear();
	_objects->damageRedAlpha_ = 0;
	_objects->player->Reset();
	_objects->SlowReset();
	_objects->plDamageRed_->SetColor(Vector4(1, 0, 0, _objects->damageRedAlpha_ / (float)_objects->player->GetMAXHP()));
	_objects->plDamageRed_->Update();
	delete leveData;
}

void GAME1Scene::Initialize() {
	_objects->SlowReset();
	_objects->player->Reset();
	_objects->player->MatUpdate();
	startTime_ = true;
	stageClear = false;
	stageFailed = false;

	//
	infoSP_ = std::make_unique<Sprite>();
	infoSP_->Initialize(_objects->spriteCommon_.get(), 60);
	infoSP_->SetSize({ 300,150 });
	infoSP_->SetPozition({ (WinApp::window_width / 1.5f) - 150,WinApp::window_height - 200 });
	isDrawSP_ = true;
	infoNum_ = 60;
	nowInfoNum_ = 0;

	isInfoWASD = false;
	isInfoSHOT = false;
	isInfoSLOW = false;
	isInfoDUSH = false;
	isInfoWEPC = false;
	isAllFalse = true;
	isTimeCount = false;
	// Json
	{
		leveData = JsonLoader::LoadJsonFile("stageDEMO");
		_objects->SetingLevel(leveData);	

	}

	{
		_controller->_camera->SetEye(camposEye);
		_controller->_camera->SetTarget(camposTar);
		_controller->_camera->SetFocalLengs(forcalLengs);
		_controller->_camera->Update();
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

void GAME1Scene::Update(Input* input) {
	_objects->eneCount = 0;
	_objects->bossCount = 0;
	_objects->floorGround->Update();
	//_objects->bossFbxO_->Update();


	if (startTime_ == true && stageClear == false && stageFailed == false) {
		startTime_ = _objects->Banner();
	}
	else if (startTime_ == false && stageClear == false && stageFailed == false) {
		_controller->_camera->SetEye(camposEye);
		_controller->_camera->SetTarget(camposTar);

#ifdef _DEBUG
		if (Input::get_instance().KeyboardPush(DIK_P)) {
			Vector3 eyeDebug = _objects->player->GetTransform().position;
			eyeDebug.y = (float)3.5f;
			_controller->_camera->SetEye(eyeDebug);
			_controller->_camera->SetTarget(_objects->player->GetReticleTransform().position);
			_controller->_camera->Update();
		}
#endif // DEBUG
		_objects->player->Update(input);
		stageFailed = _objects->player->GetIsDeath();

		_objects->damageRedAlpha_ = (float)_objects->player->GetHIT() / (float)_objects->player->GetMAXHP();
		_objects->plDamageRed_->SetColor(Vector4(1, 0, 0, _objects->damageRedAlpha_ / (float)_objects->player->GetMAXHP()));

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

		_objects->SlowEffect(_objects->player->GetIsSlow());

		if (input->KeyboardTrigger(DIK_TAB)) {
			_controller->SetSceneNum(SCE_PAUSE);
		}
		else if (_objects->eneCount == 0 && _objects->bossCount == 0) {
			stageClear = true;
		}

		if ((input->KeyboardPush(DIK_W) || input->KeyboardPush(DIK_A) || input->KeyboardPush(DIK_S) || input->KeyboardPush(DIK_D))&&nowInfoNum_ == 0) {
			isInfoWASD = true;
			isTimeCount = true;
		}
		if ((input->MouseButtonPush(0) && !input->MouseButtonPush(1))&& nowInfoNum_ == 1) {
			isInfoSHOT = true;
			isTimeCount = true;
		}
		if ((!input->MouseButtonPush(0) && input->MouseButtonPush(1))&& nowInfoNum_ == 2) {
			isInfoSLOW = true;
			isTimeCount = true;
		}
		if ((input->MouseButtonPush(0) && input->MouseButtonPush(1))&& nowInfoNum_ == 3) {
			isInfoDUSH = true;
			isTimeCount = true;
		}
		if ((input->KeyboardPush(DIK_E))&& nowInfoNum_ == 4) {
			isInfoWEPC = true;
			isTimeCount = true;

		}
		if (isTimeCount) {
			infoCountTime_++;
		}
		if (isInfoWASD == true && infoCountTime_ >= 150) {
			nowInfoNum_ = 1;
			infoNum_ = 61;
			isInfoWASD = false;
			isTimeCount = false;
			infoCountTime_ = 0;
		}
		if (isInfoSHOT == true && infoCountTime_ >= 150) {
			nowInfoNum_ = 2;
			infoNum_ = 62;
			isInfoSHOT = false;
			isTimeCount = false;
			infoCountTime_ = 0;
		}
		if (isInfoSLOW == true && infoCountTime_ >= 150) {
			nowInfoNum_ = 3;
			infoNum_ = 63;
			isInfoSLOW = false;
			isTimeCount = false;
			infoCountTime_ = 0;
		}
		if (isInfoDUSH == true && infoCountTime_ >= 150) {
			nowInfoNum_ = 4;
			infoNum_ = 64;
			isInfoDUSH = false;
			isTimeCount = false;
			infoCountTime_ = 0;
		}
		if (isInfoWEPC == true && infoCountTime_ >= 150) {
			nowInfoNum_ = 0;
			infoNum_ = 60;
			isInfoWEPC = false;
			isDrawSP_ = false;
			isTimeCount = false;
			infoCountTime_ = 0;
		}

		infoSP_->SetTextureIndex(infoNum_);
	}
	else if (startTime_ == false && stageClear == false && stageFailed == true) {
		stageFailed = _objects->Banner(1);
		if (stageFailed == false) {
			_controller->SetSceneNum(SCE_GAME1);
		}
	}
	else if (startTime_ == false && stageClear == true && stageFailed == false) {
		stageClear = _objects->Banner(2);
		if (stageClear == false) {
			_controller->SetSceneNum(SCE_CLEAR);
		}
	}
	_objects->UIUpdate();
}

void GAME1Scene::Draw() {
	_objects->floorGround->Draw(_controller->_dxCommon);
	for (std::unique_ptr <Enemy>& enemy : _objects->enemys) {
		enemy->Draw(_controller->_dxCommon);
	}
	for (std::unique_ptr <Boss>& boss : _objects->boss) {
		boss->Draw(_controller->_dxCommon);
	}
	for (std::unique_ptr <Wall>& walls : _objects->walls) {
		walls->Draw(_controller->_dxCommon);
	}
	//_objects->bossFbxO_->Draw(_controller->_dxCommon->GetCommandList());

	Object3d::PreDraw(_controller->_dxCommon->GetCommandList());

	BulletManager::GetInstance()->Draw();

	Object3d::PostDraw();
	if (startTime_ == false) {
		_objects->player->Draw(_controller->_dxCommon);
	}
	_objects->SlowEffectDraw();
	_objects->plDamageRed_->Draw();
	_objects->UIDraw();
	if (startTime_ == false && stageClear == false && stageFailed == false && isDrawSP_ == true) {
		//infoSP_->Draw();
	}
	if (startTime_ == true || stageFailed == true || stageClear == true) {
		_objects->BannerDraw();
	}
}