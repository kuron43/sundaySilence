#include "SceneIntegrate.h"



TitleScene::TitleScene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}
TitleScene::~TitleScene() {

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
}

void TitleScene::Initialize() {
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();

	particle_ = new ParticleManager();
	particle_->Initialize();
	particle_->LoadTexture("yellow.png");
	particle_->Update();

	title_ = std::make_unique<Sprite>();
	title_->Initialize(_objects->spriteCommon_.get(), 1);
	title_->SetSize({ 600,300 });
	title_->SetPozition(titlePos);
	titleButton_ = std::make_unique<Sprite>();
	titleButton_->Initialize(_objects->spriteCommon_.get(), 8);
	titleButton_->SetSize({ 256,128 });
	titleButton_->SetPozition({ WinApp::window_width / 2.5f,WinApp::window_height / 1.5f });

	red_ = std::make_unique<Sprite>();
	red_->Initialize(_objects->spriteCommon_.get(), 8);
	red_->SetSize({ 24,24 });
	red_->SetPozition({ WinApp::window_width / 2.5f,WinApp::window_height / 1.5f });

	titleTime_ = 0;
	sinMoveTitle = 0.0f;
	titlePos = { 20,10 };

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
	for (Wall* walls : _objects->walls) {
		walls->Update();
	}
	for (Enemy* enemy : _objects->enemys) {
		enemy->Update();
	}
	for (Boss* boss : _objects->boss) {
		boss->Update();
	}
}

void TitleScene::Update(Input* input) {
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();
	if (titleTime_ % 50 == 0) {
		particle_->RandParticle(Vector3(0, 100, 0), 100);
	}
	particle_->Update();

	_objects->mouseCursor_->Update(input);
	_objects->floorGround->Update();

	sinMoveTitle = 10 + sin(3.1415f / 2 / 120 * titleTime_) * 30;
	titleTime_++;
	titlePos.y = sinMoveTitle;
	title_->SetPozition(titlePos);

	title_->Update();
	titleButton_->Update();

	_objects->player->Update(input, true);

	if (input->KeyboardTrigger(DIK_NUMPAD1)) {
		_controller->PushScene(new PauseScene(_controller, _objects));
	}
	if (_objects->mouseCursor_->Cursor2Sprite(titleButton_.get())) {
		if (input->MouseButtonTrigger(0)) {
			_controller->SetSceneNum(SCE_SELECT);
		}
		titleButton_->SetTextureIndex(9);
	}
	else {
		titleButton_->SetTextureIndex(8);
	}
}

void TitleScene::Draw() {
	_objects->floorGround->Draw(_controller->_dxCommon);
	for (Enemy* enemy : _objects->enemys) {
		enemy->Draw(_controller->_dxCommon);
	}
	for (Boss* boss : _objects->boss) {
		boss->Draw(_controller->_dxCommon);
	}
	for (Wall* walls : _objects->walls) {
		walls->Draw(_controller->_dxCommon);
	}

	particle_->Draw();
	title_->Draw();
	titleButton_->Draw();

	_objects->player->Draw(_controller->_dxCommon);
	_objects->mouseCursor_->Draw();
}



