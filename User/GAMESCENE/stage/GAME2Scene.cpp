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
	for (Wall* walls : _objects->walls) {
		walls->Reset();
	}
	for (Enemy* enemy : _objects->enemys) {
		enemy->Reset();
	}
	for (Boss* boss : _objects->boss) {
		boss->Reset();
	}

	_objects->walls.clear();
	_objects->enemys.clear();
	_objects->boss.clear();
	delete leveData;
}

void GAME2Scene::Initialize() {

	_objects->player->SetPos(Vector3(0, 0, 0));
	_objects->player->MatUpdate();
	startTime_ = true;

	// Json
	{
		leveData = JsonLoader::LoadJsonFile("gamedemo");

		for (auto& objectData : leveData->JsonObjects) {

			if (objectData.fileName == "enemy") {
				Enemy* newEnemy = new Enemy();
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
				_objects->enemys.emplace_back(newEnemy);
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
				newWall->object_->SetColor(Vector3(0.5f, 0.3f, 0.3f));
				newWall->object_->Update();
				newWall->CollideInitialize();
				_objects->walls.emplace_back(newWall);
			}
			if (objectData.fileName == "boss") {
				Boss* newBoss = new Boss();
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
				_objects->boss.emplace_back(newBoss);
			}

		}

	}

	{
		_controller->_camera->SetEye(camposEye);
		_controller->_camera->SetTarget(camposTar);
		_controller->_camera->Update();
		_objects->floorGround->Update();

		BulletManager::GetInstance()->Update();
		for (Enemy* enemy : _objects->enemys) {
			enemy->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
			enemy->Update();
			if (!enemy->HowDead()) {
				_objects->eneCount++;
			}
		}
		for (Boss* boss : _objects->boss) {
			boss->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
			boss->Update();
			if (!boss->HowDead()) {
				_objects->bossCount++;
			}
		}
		for (Wall* walls : _objects->walls) {
			walls->Update();
		}
	}
}

void GAME2Scene::Update(Input* input) {
	_objects->eneCount = 0;
	_objects->bossCount = 0;

	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();
	if (startTime_) {
		startTime_ = _objects->Ready();
	}
	else {

		_objects->floorGround->Update();
		for (Wall* walls : _objects->walls) {
			walls->Update();
		}
		_objects->player->Update(input);

		BulletManager::GetInstance()->Update();
		for (Enemy* enemy : _objects->enemys) {
			enemy->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
			enemy->Update(input);
			if (!enemy->HowDead()) {
				_objects->eneCount++;
			}
		}
		for (Boss* boss : _objects->boss) {
			boss->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
			boss->Update(input);
			if (!boss->HowDead()) {
				_objects->bossCount++;
			}
		}


		ImGui::Begin("enecount");
		ImGui::Text("countE : %d", _objects->eneCount);
		ImGui::Text("countB : %d", _objects->bossCount);
		ImGui::End();

		if (input->KeyboardTrigger(DIK_TAB)) {
			_controller->SetSceneNum(SCE_PAUSE);
		}
		else if (_objects->eneCount == 0 && _objects->bossCount == 0) {
			_controller->SetSceneNum(SCE_OVER);
		}
	}
}

void GAME2Scene::Draw() {
	_objects->floorGround->Draw(_controller->_dxCommon);
	_objects->player->Draw(_controller->_dxCommon);
	for (Enemy* enemy : _objects->enemys) {
		enemy->Draw(_controller->_dxCommon);
	}
	for (Boss* boss : _objects->boss) {
		boss->Draw(_controller->_dxCommon);
	}
	for (Wall* walls : _objects->walls) {
		walls->Draw(_controller->_dxCommon);
	}

	Object3d::PreDraw(_controller->_dxCommon->GetCommandList());

	BulletManager::GetInstance()->Draw();

	Object3d::PostDraw();

	if (startTime_) {
		_objects->ReadyDraw();
	}
}