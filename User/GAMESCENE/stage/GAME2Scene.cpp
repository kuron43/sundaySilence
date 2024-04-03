/**
 * @file GAME2Scene.cpp
 * @brief ゲーム実行2ステージ目
 */
#include "GAME2Scene.h"
#include "SceneManager.h"
GAME2Scene::GAME2Scene(SceneManager* manager, SceneObjects* objects) {
	_manager = manager;
	_objects = objects;
}

GAME2Scene::~GAME2Scene() {
	BulletManager::GetInstance()->AllClearBullet();
	_objects->walls.clear();
	_objects->enemys.clear();
	_objects->boss.clear();
	_objects->damageRedAlpha_ = 0;
	_objects->player->Reset();
	_objects->plDamageRed_->SetColor(Vector4(1, 0, 0, _objects->damageRedAlpha_ / 10.0f));
	_objects->plDamageRed_->Update();
}

void GAME2Scene::Initialize() {
	_objects->SlowReset();
	_objects->player->Reset();
	_objects->player->MatUpdate();
	startTime_ = true;
	stageClear = false;
	stageFailed = false;

	{
		_manager->_camera->SetEye(camposEye);
		_manager->_camera->SetTarget(camposTar);
		_manager->_camera->SetFocalLengs(forcalLengs);
		_manager->_camera->Update();
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

void GAME2Scene::Update(Input* input) {
	_objects->eneCount = 0;
	_objects->bossCount = 0;
	_objects->floorGround->Update();


	if (startTime_ == true && stageClear == false && stageFailed == false) {
		startTime_ = _objects->Banner();
	}
	else if (startTime_ == false && stageClear == false && stageFailed == false) {
		_manager->_camera->SetEye(camposEye);
		_manager->_camera->SetTarget(camposTar);

		if (Input::get_instance().KeyboardPush(DIK_P)) {
			Vector3 eyeDebug = _objects->player->GetTransform().position;
			eyeDebug.y = (float)1;
			_manager->_camera->SetEye(eyeDebug);
			_manager->_camera->SetTarget(_objects->player->GetReticleTransform().position);
			_manager->_camera->Update();
		}
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
			_manager->SetSceneNum(SCE_PAUSE);
		}
		else if (_objects->eneCount == 0 && _objects->bossCount == 0) {
			//_manager->SetSceneNum(SCE_SELECT);
			stageClear = true;
		}
	}
	else if (startTime_ == false && stageClear == false && stageFailed == true) {
		stageFailed = _objects->Banner(1);
		if (stageFailed == false) {
			_manager->SetSceneNum(_manager->GetSceneNum());
		}
	}
	else if (startTime_ == false && stageClear == true && stageFailed == false) {
		stageClear = _objects->Banner(2);
		if (stageClear == false) {
			_manager->SetSceneNum(SCE_CLEAR);
		}
	}
	_objects->UIUpdate();
}

void GAME2Scene::Draw() {
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

	Object3d::PreDraw(_manager->_dxCommon->GetCommandList());

	BulletManager::GetInstance()->Draw();

	Object3d::PostDraw();
	if (startTime_ == false) {
		_objects->player->Draw(_manager->_dxCommon);
	}
	_objects->SlowEffectDraw();
	_objects->plDamageRed_->Draw();
	_objects->UIDraw();
	if (startTime_ == true || stageFailed == true || stageClear == true) {
		_objects->BannerDraw();
	}

}