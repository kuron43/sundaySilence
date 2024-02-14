/**
 * @file TitleScene.cpp
 * @brief
 */
#include "SceneIntegrate.h"

TitleScene::TitleScene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}
TitleScene::~TitleScene() {
	_objects->walls.clear();
	_objects->enemys.clear();
	_objects->boss.clear();
	delete leveData;
	particle_.reset();
	titleButton_.reset();
	title_.reset();
	red_.reset();
}

void TitleScene::Initialize() {
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->SetFocalLengs(forcalLengs);
	_controller->_camera->Update();

	particle_ = std::make_unique<ParticleManager>();
	particle_->Initialize();
	particle_->LoadTexture("yellow.png");
	

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
	_objects->player->Reset();

	// Json
	{
		leveData = JsonLoader::LoadJsonFile("title");
		_objects->SetingLevel(leveData);
	}
	{
		_controller->_camera->SetEye(camposEye);
		_controller->_camera->SetTarget(camposTar);
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
		for (std::unique_ptr <Wall>& walls : _objects->walls) {
			walls->Update();
		}
	}
}

void TitleScene::Update(Input* input) {
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();
	if (titleTime_ % 50 == 0) {
		particle_->RandParticle(100,Vector3(0, 100, 0));
	}
	particle_->Update();

	_objects->mouseCursor_->Update(input);
	_objects->floorGround->Update();
	_objects->player->Update(input, true);

	sinMoveTitle = 10.0f + sin(3.1415f / 2.0f / 120.0f * titleTime_) * 30.0f;
	titleTime_++;
	titlePos.y = sinMoveTitle;
	title_->SetPozition(titlePos);

	title_->Update();
	titleButton_->Update();


	if (input->KeyboardTrigger(DIK_NUMPAD1)) {
		_controller->SetSceneNum(SCE_PAUSE);
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
	for (std::unique_ptr <Enemy>& enemy : _objects->enemys) {
		enemy->Draw(_controller->_dxCommon);
	}
	for (std::unique_ptr <Boss>& boss : _objects->boss) {
		boss->Draw(_controller->_dxCommon);
	}
	for (std::unique_ptr <Wall>& walls : _objects->walls) {
		walls->Draw(_controller->_dxCommon);
	}
	_objects->player->Draw(_controller->_dxCommon);

	particle_->Draw();
	title_->Draw();
	titleButton_->Draw();

	_objects->mouseCursor_->Draw();
}



