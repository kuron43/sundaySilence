#include "TitleScene.h"
#include "SceneManager.h"

#include "GAME1Scene.h"



TitleScene::TitleScene(SceneManager* controller) {
	_controller = controller;
}
TitleScene::~TitleScene() {
	delete spriteCommon;
	delete sprite;
}

void TitleScene::Initialize(DirectXCommon* dxCommon) {
	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	sprite = new Sprite();

	Vector2 spritePOS = sprite->GetPosition();
	sprite->Initialize(spriteCommon);
	sprite->SetPozition(spritePOS);
	sprite->SetSize(Vector2{ WinApp::window_width / 3,WinApp::window_height / 3 });

	spriteCommon->LoadTexture(0, "1.png");
	sprite->SetTextureIndex(0);
}

void TitleScene::Update(Input* input) {

	if (input->KeyboardTrigger(DIK_SPACE) || input->Pad_X_ButtonTrigger(LB)) {
		_controller->ChangeScene(new GAME1Scene(_controller));
		
	}
}

void TitleScene::Draw(DirectXCommon* dxCommon) {
	sprite->Draw();
}