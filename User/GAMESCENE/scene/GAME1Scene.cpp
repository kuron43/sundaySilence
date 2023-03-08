#include "GAME1Scene.h"
#include "SceneManager.h"

#include "EndScene.h"


GAME1Scene::GAME1Scene(SceneManager* controller) {
	_controller = controller;
}

GAME1Scene::~GAME1Scene() {
	delete skydome, skydomeMD;
}

void GAME1Scene::Initialize(DirectXCommon* dxCommon) {

	skydomeMD = Model::LoadFromOBJ("skydome");

	skydome = Object3d::Create();

	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });
	skydome->Update();

}

void GAME1Scene::Update(Input* input) {

	skydome->Update();
	if (input->KeyboardTrigger(DIK_SPACE) || input->Pad_X_ButtonTrigger(LB)) {
		_controller->ChangeScene(new EndScene(_controller));
	}
}

void GAME1Scene::Draw(DirectXCommon* dxCommon) {

	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());

	skydome->Draw();

	//3Dオブジェクト描画後処理
	Object3d::PostDraw();
}