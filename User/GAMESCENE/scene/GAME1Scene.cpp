#include "GAME1Scene.h"
#include "SceneManager.h"

#include "SceneIntegrate.h"


GAME1Scene::GAME1Scene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}

GAME1Scene::~GAME1Scene() {
	_objects->walls.clear();
	_objects->enemys.clear();
}

void GAME1Scene::Initialize() {

	_objects->player->SetPos(Vector3(0,0,0));
	_objects->player->MatUpdate();


	// Json
	{
		leveData = JsonLoader::LoadJsonFile("game3");

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
				newWall->object_->SetColor(Vector4(0.5f, 0.3f, 0.3f, 0.3f));
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
}

void GAME1Scene::Update(Input* input) {
	_objects->eneCount = 0;

	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();

	_objects->player->Update(input);
	for (Wall* walls : _objects->walls) {
		walls->Update();
	}

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
	ImGui::Text("count : %d", _objects->eneCount);
	ImGui::End();

	if (input->KeyboardTrigger(DIK_NUMPAD1)) {
		_controller->PushScene(new PauseScene(_controller, _objects));
	}
	else if (input->KeyboardTrigger(DIK_RETURN)) {
		for (Enemy* enemy : _objects->enemys) {
			enemy->Reset();
		}
		for (Boss* boss : _objects->boss) {
			boss->Reset();
		}
		_controller->ChangeScene(new EndScene(_controller, _objects));
	}
}

void GAME1Scene::Draw() {
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

}