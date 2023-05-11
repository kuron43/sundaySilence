#include "GAME1Scene.h"
#include "SceneManager.h"

//#include "EndScene.h"
#include "TitleScene.h"


GAME1Scene::GAME1Scene(SceneManager* controller) {
	_controller = controller;
}

GAME1Scene::~GAME1Scene() {
	delete obj2, obj2MD;
}

void GAME1Scene::Initialize(DirectXCommon* dxCommon, Camera* _camera) {

	obj2MD = Model::LoadFromOBJ("sphere");

	obj2 = Object3d::Create();

	obj2->SetModel(obj2MD);
	obj2->wtf.scale = (Vector3{ 10, 10, 10 });
	obj2->Update();

}

void GAME1Scene::Update(Input* input, Camera* _camera) {

	obj2->wtf.position.y = -5;

	obj2->Update();

	if (input->KeyboardPush(DIK_1)) {
		obj2->wtf.rotation.y += 0.1;
	}
	if (input->KeyboardPush(DIK_2)) {
		obj2->wtf.rotation.x += 0.1;
	}
	if (input->KeyboardPush(DIK_3)) {
		obj2->wtf.rotation.z += 0.1;
	}
	if (input->KeyboardTrigger(DIK_RETURN) || input->Pad_X_ButtonTrigger(LB)) {
		_controller->ChangeScene(new TitleScene(_controller));
	}
}

void GAME1Scene::Draw(DirectXCommon* dxCommon) {

	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());

	obj2->Draw();

	//3Dオブジェクト描画後処理
	Object3d::PostDraw();
}