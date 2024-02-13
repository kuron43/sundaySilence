/**
 * @file GAME2Scene.cpp
 * @brief ゲーム実行2ステージ目
 */
#include "GAME2Scene.h"
#include "SceneManager.h"
GAME2Scene::GAME2Scene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
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
	delete leveData;
}

void GAME2Scene::Initialize() {
	_objects->SlowReset();
	_objects->player->Reset();
	_objects->player->MatUpdate();
	startTime_ = true;
	stageClear = false;
	stageFailed = false;
	// Json
	{
		leveData = JsonLoader::LoadJsonFile("stageDemo2");

		for (auto& objectData : leveData->JsonObjects) {

			if (objectData.fileName == "enemy") {
				Enemy* newEnemy = new Enemy();
				if (objectData.weapon == "ASSAULT") {
					newEnemy->SetWeaponNum(WP_ASSAULT);
				}if (objectData.weapon == "SHOTGUN") {
					newEnemy->SetWeaponNum(WP_SHOTGUN);
				}if (objectData.weapon == "BOMFIRE") {
					newEnemy->SetWeaponNum(WP_BOMFIRE);
				}
				newEnemy->Initialize();
				//座標
				Vector3 pos;
				pos = objectData.translation;
				newEnemy->object_->wtf.position = pos;
				//回転
				Vector3 rot;
				rot = objectData.rotation;
				newEnemy->object_->wtf.rotation = rot;
				newEnemy->SetRestRotate(rot);
				//拡縮
				Vector3 sca;
				sca = objectData.scaling;
				newEnemy->object_->wtf.scale = sca;
				//newEnemy->object_->SetColor(Vector4(0.5f, 1, 1, 0));
				_objects->enemys.emplace_back(std::move(newEnemy));
			}
			if (objectData.fileName == "wall") {
				Wall* newWall = new Wall();
				newWall->Initialize(_objects->wallMD);
				//座標
				Vector3 pos;
				pos = objectData.translation;
				newWall->object_->wtf.position = pos;
				//回転
				Vector3 rot;
				rot = objectData.rotation;
				newWall->object_->wtf.rotation = rot;
				//拡縮
				Vector3 sca;
				sca = objectData.scaling;
				newWall->object_->wtf.scale = sca;
				newWall->object_->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
				newWall->object_->Update();
				newWall->CollideInitialize();
				_objects->walls.emplace_back(std::move(newWall));
			}
			if (objectData.fileName == "boss") {
				Boss* newBoss = new Boss();
				if (objectData.weapon == "ASSAULT") {
					newBoss->SetWeaponNum(WP_ASSAULT);
				}if (objectData.weapon == "SHOTGUN") {
					newBoss->SetWeaponNum(WP_SHOTGUN);
				}if (objectData.weapon == "BOMFIRE") {
					newBoss->SetWeaponNum(WP_BOMFIRE);
				}
				newBoss->SetFBXModel(_objects->bossFbxM_.get());
				newBoss->Initialize();
				//座標
				Vector3 pos;
				pos = objectData.translation;
				newBoss->object_->wtf.position = pos;
				//回転
				Vector3 rot;
				rot = objectData.rotation;
				newBoss->object_->wtf.rotation = rot;
				newBoss->SetRestRotate(rot);
				//拡縮
				Vector3 sca;
				sca = objectData.scaling;
				newBoss->object_->wtf.scale = sca;
				//newBoss->object_->SetColor(Vector4(0.5f, 1, 1, 0));
				_objects->boss.emplace_back(std::move(newBoss));
			}
			if (objectData.fileName == "player") {
				Vector3 position = objectData.translation;
				_objects->player->SetPos(position);
			}

		}

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

void GAME2Scene::Update(Input* input) {
	_objects->eneCount = 0;
	_objects->bossCount = 0;
	_objects->floorGround->Update();


	if (startTime_ == true && stageClear == false && stageFailed == false) {
		startTime_ = _objects->Banner();
	}
	else if (startTime_ == false && stageClear == false && stageFailed == false) {
		_controller->_camera->SetEye(camposEye);
		_controller->_camera->SetTarget(camposTar);

		if (Input::get_instance().KeyboardPush(DIK_P)) {
			Vector3 eyeDebug = _objects->player->GetTransform().position;
			eyeDebug.y = (float)1;
			_controller->_camera->SetEye(eyeDebug);
			_controller->_camera->SetTarget(_objects->player->GetReticleTransform().position);
			_controller->_camera->Update();
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
			_controller->SetSceneNum(SCE_PAUSE);
		}
		else if (_objects->eneCount == 0 && _objects->bossCount == 0) {
			//_controller->SetSceneNum(SCE_SELECT);
			stageClear = true;
		}
	}
	else if (startTime_ == false && stageClear == false && stageFailed == true) {
		stageFailed = _objects->Banner(1);
		if (stageFailed == false) {
			_controller->SetSceneNum(SCE_GAME2);
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

void GAME2Scene::Draw() {
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

	Object3d::PreDraw(_controller->_dxCommon->GetCommandList());

	BulletManager::GetInstance()->Draw();

	Object3d::PostDraw();
	if (startTime_ == false) {
		_objects->player->Draw(_controller->_dxCommon);
	}
	_objects->SlowEffectDraw();
	_objects->plDamageRed_->Draw();
	_objects->UIDraw();
	if (startTime_ == true || stageFailed == true || stageClear == true) {
		_objects->BannerDraw();
	}

}