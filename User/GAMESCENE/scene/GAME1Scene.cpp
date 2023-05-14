#include "GAME1Scene.h"
#include "SceneManager.h"

#include "SceneIntegrate.h"


GAME1Scene::GAME1Scene(SceneManager* controller) {
	_controller = controller;
}

GAME1Scene::~GAME1Scene() {
	delete obj2, obj2MD;
	delete obj3, obj3MD;
}

void GAME1Scene::Initialize(DirectXCommon* dxCommon, Camera* _camera) {

	obj2MD = Model::LoadFromOBJ("sphere");

	obj2 = Object3d::Create();

	obj2->SetModel(obj2MD);
	obj2->wtf.scale = (Vector3{ 10, 10, 10 });
	obj2->Update();

	obj3MD = Model::LoadFromOBJ("ball");

	obj3 = Object3d::Create();

	obj3->SetModel(obj3MD);
	obj3->wtf.scale = (Vector3{ 10, 10, 10 });
	obj3->Update();

}

void GAME1Scene::Update(Input* input, Camera* _camera) {

	obj2->wtf.position.x = 10;
	obj3->wtf.position.x = -10;

	obj2->wtf.position.z = 10;
	obj3->wtf.position.z = -10;

	obj2->Update();
	obj3->Update();

	if (input->KeyboardPush(DIK_W)) {
		obj2->wtf.rotation.y += 0.1;
		obj3->wtf.rotation.y += 0.1;
	}
	if (input->KeyboardPush(DIK_S)) {
		obj2->wtf.rotation.y -= 0.1;
		obj3->wtf.rotation.y -= 0.1;
	}
	if (input->KeyboardPush(DIK_A)) {
		obj2->wtf.rotation.x += 0.1;
		obj3->wtf.rotation.x += 0.1;
	}
	if (input->KeyboardPush(DIK_D)) {
		obj2->wtf.rotation.z += 0.1;
		obj3->wtf.rotation.z += 0.1;
	}

	

	if (input->KeyboardTrigger(DIK_RETURN) || input->Pad_X_ButtonTrigger(LB)) {
		_controller->ChangeScene(new TitleScene(_controller));
	}
}

void GAME1Scene::Draw(DirectXCommon* dxCommon) {

	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());

	//obj2->Draw();
	obj3->Draw();

	//3Dオブジェクト描画後処理
	Object3d::PostDraw();
}