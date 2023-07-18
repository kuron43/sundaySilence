#include "Wall.h"
#include "DirectXCommon.h"
#include "imgui.h"

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
	//obbPos_ = Affin::GetWorldTrans(object_->wtf.matWorld);
	//obbLength_ = Vector3(10, 10, 10);
	obb_ = new ObbCollider;
	obb_->CreateOBB(object_->model_->GetVertices(), &object_->wtf);
	CollisionManager::GetInstance()->AddCollider(obb_);
	obb_->SetObject3d(coliderPosTest_);
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
	isHit = false;
	object_->Update();
	coliderPosTest_->wtf.position = obb_->GetPos_();
	coliderPosTest_->wtf.scale.x = obb_->GetLength(0);
	coliderPosTest_->wtf.scale.y = obb_->GetLength(1);
	coliderPosTest_->wtf.scale.z = obb_->GetLength(2);
	coliderPosTest_->wtf.rotation = obb_->Getrotate_();
	coliderPosTest_->Update();




	if (obb_->GetIsHit() == true && obb_->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_ENEMIEBULLETS) {
		//CollisionManager::GetInstance()->RemoveCollider(obb_);
		Vector3 a = { 0,0,0 };
		ImGui::Begin("Wall");
		ImGui::Text("Hit");
		ImGui::End();
		isHit = true;
	}
	/*ImGui::Begin("WallPOS");
	ImGui::Text("pos:%f,%f,%f", obb_->GetPos_().x, obb_->GetPos_().y, obb_->GetPos_().z);
	ImGui::Text("Len:%f,%f,%f", obb_->GetLength(0), obb_->GetLength(1), obb_->GetLength(2));
	ImGui::Text("Dir:%f,%f,%f", obb_->GetLength(0), obb_->GetLength(1), obb_->GetLength(2));

	ImGui::End();*/
	obb_->Update();
	//obb_->UpdateObb(*object_);
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
	delete model_;
	CollisionManager::GetInstance()->RemoveCollider(obb_);
	delete obb_;


}