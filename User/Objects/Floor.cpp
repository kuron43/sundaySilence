/**
 * @file Floor.cpp
 * @brief
 */
#include "Floor.h"

#include "DirectXCommon.h"
#pragma warning(push)
#pragma warning(disable: 4514)
#include <imgui.h>
#pragma warning(pop)

Floor::Floor() {

}
Floor::~Floor() {
	delete object_;
}

/// 更新を行う
void Floor::Initialize(Model* model) {
	object_ = Object3d::Create();
	object_->SetModel(model);
	object_->Initialize();
	object_->transForm.position.y = -0.8f;
	object_->transForm.scale.x = 15.5f;
	object_->transForm.scale.z = 15.5f;
	object_->UpdateMatrix();
}

void Floor::CollideInitialize() {

}

/// 更新を行う
void Floor::Update() {
	isHit = false;
	object_->Update();
}

/// 描画を行う
void Floor::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	object_->Draw();
	Object3d::PostDraw();
}

/// リセットを行う
void Floor::Reset() {
}