#include "GAME1Scene.h"
#include "SceneManager.h"

#include "SceneIntegrate.h"


GAME1Scene::GAME1Scene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}

GAME1Scene::~GAME1Scene() {
	_objects->walls.clear();
}

void GAME1Scene::Initialize() {
	Vector3 enepos = { -10,0,10 };
	for (Enemy* enemy : _objects->enemys) {
		enemy->SetPos(enepos);
		enepos.x += 5;
	}

	// Json
	{
		leveData = JsonLoader::LoadJsonFile("game2");

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
				//拡縮
				Vector3 sca;
				sca = objectData.scaling;
				newEnemy->object_->wtf.scale = sca;
				newEnemy->object_->SetColor(Vector4(0.5f, 1, 1, 0));
				_objects->enemys.emplace_back(newEnemy);
			}
			if (objectData.fileName == "wall") {
				Object3d* newWall = Object3d::Create();
				newWall->SetModel(_objects->wallMD);
				newWall->Initialize();
				//座標
				Vector3 pos;
				pos = objectData.translation;
				newWall->wtf.position = pos;
				//回転
				Vector3 rot;
				rot = objectData.rotation;
				newWall->wtf.rotation = rot;
				//拡縮
				Vector3 sca;
				sca = objectData.scaling;
				newWall->wtf.scale = sca;
				newWall->SetColor(Vector4(0.5f, 0.3f, 0.3f, 0.3f));
				_objects->walls.emplace_back(newWall);
			}

		}

	}
}

void GAME1Scene::Update(Input* input) {
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();
	_objects->player->Update(input);
	for (Object3d* walls : _objects->walls) {
		walls->Update();
	}

	for (Enemy* enemy : _objects->enemys) {
		enemy->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
		enemy->Update(input);
	}

	if (input->KeyboardTrigger(DIK_NUMPAD1)) {
		_controller->PushScene(new PauseScene(_controller, _objects));
	}
	else if (input->KeyboardTrigger(DIK_RETURN)) {
		_controller->ChangeScene(new EndScene(_controller, _objects));
	}
}

void GAME1Scene::Draw() {
	_objects->player->Draw(_controller->_dxCommon);
	for (Enemy* enemy : _objects->enemys) {
		enemy->Draw(_controller->_dxCommon);
	}
	Object3d::PreDraw(_controller->_dxCommon->GetCommandList());
	for (Object3d* walls : _objects->walls) {
		walls->Draw();
	}
	Object3d::PostDraw();
}