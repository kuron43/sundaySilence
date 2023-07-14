#include "Wall.h"
#include "DirectXCommon.h"

Wall::Wall() {

}
Wall::~Wall() {

}

/// 更新を行う
void Wall::Initialize(Model* model) {
	object_ = Object3d::Create();
	object_->SetModel(model);
	object_->Initialize();

	
}

void Wall::CollideInitialize() {
	obbPos_ = Affin::GetWorldTrans(object_->wtf.matWorld);
	obbLength_ = Vector3(10, 10, 10);
	obb_ = new ObbCollider;
	obb_->CreateOBB(object_);
	CollisionManager::GetInstance()->AddCollider(obb_);
	obb_->Update();
	obb_->SetAttribute(COLLISION_ATTR_BARRIEROBJECT);
	//test
	coliderPosTest_ = Object3d::Create();
	coliderPosTest_->SetModel(Model::LoadFromOBJ("cube"));
	coliderPosTest_->wtf.position = obb_->GetPos_();
	coliderPosTest_->wtf.scale.x = obb_->GetLength(0);
	coliderPosTest_->wtf.scale.y = obb_->GetLength(1);
	coliderPosTest_->wtf.scale.z = obb_->GetLength(2);
	coliderPosTest_->wtf.rotation = obb_->Getrotate_();
	coliderPosTest_->Update();
}

/// 更新を行う
void Wall::Update() {
	object_->Update();
	coliderPosTest_->wtf.position = obb_->GetPos_();
	coliderPosTest_->wtf.scale.x = obb_->GetLength(0);
	coliderPosTest_->wtf.scale.y = obb_->GetLength(1);
	coliderPosTest_->wtf.scale.z = obb_->GetLength(2);
	coliderPosTest_->wtf.rotation = obb_->Getrotate_();
	coliderPosTest_->Update();




	if (obb_->GetIsHit() == true && obb_->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_PLAYERBULLETS) {
		//CollisionManager::GetInstance()->RemoveCollider(obb_);
		Vector3 a = { 0,0,0 };
	}
	//obb_->UpdateObb(*object_);
	obb_->Update();
}

/// 描画を行う
void Wall::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	//object_->Draw();
	if (!obb_->GetIsHit()) {

	coliderPosTest_->Draw();
	}
	Object3d::PostDraw();

}

/// リセットを行う
void Wall::Reset() {

}