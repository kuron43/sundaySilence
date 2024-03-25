/**
 * @file Wall.cpp
 * @brief
 */
#include "Wall.h"
#include "DirectXCommon.h"
#pragma warning(push)
#pragma warning(disable: 4514)
#include <imgui.h>
#pragma warning(pop)

Wall::Wall() {

}
Wall::~Wall() {

	delete model_;
	CollisionManager::GetInstance()->RemoveCollider(obb_);
	delete obb_;
	delete object_;
	delete colliderPosTest_;
}

/// 更新を行う
void Wall::Initialize(Model* model) {
	object_ = Object3d::Create();
	object_->SetModel(model);
}

void Wall::CollideInitialize() {
	obb_ = new ObbCollider;
	obb_->SetObject3d(object_);
	obb_->CreateOBB(object_->model_->GetVertices(), &object_->wtf);
	CollisionManager::GetInstance()->AddCollider(obb_);
	obb_->Update();
	obb_->SetAttribute(COLLISION_ATTR_BARRIEROBJECT);
	//test
	model_ = Model::LoadFromOBJ("wall");
	colliderPosTest_ = Object3d::Create();
	colliderPosTest_->SetModel(model_);
	colliderPosTest_->wtf.position = obb_->GetPos_();
	colliderPosTest_->wtf.scale.x = obb_->GetLength(0);
	colliderPosTest_->wtf.scale.y = obb_->GetLength(1);
	colliderPosTest_->wtf.scale.z = obb_->GetLength(2);
	colliderPosTest_->wtf.rotation = obb_->Getrotate_();
	colliderPosTest_->Update();
}

/// 更新を行う
void Wall::Update() {
	isHit = false;
	obb_->Update();
	object_->SetColor({ 0.5f,0.5f,0.5f,1.0f});
	object_->wtf.position = obb_->GetPos_();
	object_->wtf.scale.x = obb_->GetLength(0);
	object_->wtf.scale.y = obb_->GetLength(1);
	object_->wtf.scale.z = obb_->GetLength(2);
	object_->wtf.rotation = obb_->Getrotate_();
	object_->Update();
	colliderPosTest_->wtf.position = obb_->GetPos_();
	colliderPosTest_->wtf.scale.x = obb_->GetLength(0);
	colliderPosTest_->wtf.scale.y = obb_->GetLength(1);
	colliderPosTest_->wtf.scale.z = obb_->GetLength(2);
	colliderPosTest_->wtf.rotation = obb_->Getrotate_();
	colliderPosTest_->Update();

}

/// 描画を行う
void Wall::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	object_->Draw();
	//colliderPosTest_->Draw();
	Object3d::PostDraw();
}

/// リセットを行う
void Wall::Reset() {
	delete model_;
	CollisionManager::GetInstance()->RemoveCollider(obb_);
	delete obb_;
}