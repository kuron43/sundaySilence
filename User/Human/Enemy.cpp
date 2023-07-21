#include "Enemy.h"

Enemy::Enemy() {

}
Enemy::~Enemy() {
	delete model_;
	delete weapon_;
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		delete sphere[i];

	}
}

///
void Enemy::Initialize() {
	isDead = false;
	nowTitle = false;
	model_ = Model::LoadFromOBJ("cube");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

	reticle = Object3d::Create();
	reticle->SetModel(model_);
	reticle->Initialize();

	weapon_ = new Assault();
	weapon_->Initialize();

	//当たり判定用
	SPHERE_COLISSION_NUM = 1;
	sphere.resize(SPHERE_COLISSION_NUM);
	spherePos.resize(SPHERE_COLISSION_NUM);
	//FbxO_.get()->isBonesWorldMatCalc = true;	// ボーンの行列を取得するか
	coliderPosTest_.resize(SPHERE_COLISSION_NUM);

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		sphere[i] = new SphereCollider;
		CollisionManager::GetInstance()->AddCollider(sphere[i]);
		spherePos[i] = Affin::GetWorldTrans(object_->wtf.matWorld);
		sphere[i]->SetObject3d(object_);
		sphere[i]->SetBasisPos(&spherePos[i]);
		sphere[i]->SetRadius(1.0f);
		sphere[i]->Update();
		sphere[i]->SetAttribute(COLLISION_ATTR_ENEMIES);
		////test
		//coliderPosTest_[i] = Object3d::Create();
		//coliderPosTest_[i]->SetModel(model_);
		//coliderPosTest_[i]->wtf.m_Pos = sphere[i]->center;
		//coliderPosTest_[i]->wtf.scale = Vector3{ sphere[i]->GetRadius(),sphere[i]->GetRadius() ,sphere[i]->GetRadius() };
		//coliderPosTest_[i]->wtf.rotation = { 0,0,0 };
		//coliderPosTest_[i]->Update();
	}
	/*ray = new Ray;
	Vector3 rayvec = Affin::GetWorldTrans(reticle->wtf.matWorld) - Affin::GetWorldTrans(object_->wtf.matWorld);
	ray->start = Affin::GetWorldTrans( object_->wtf.matWorld);
	ray->dir = rayvec;
	CollisionManager::GetInstance()->Raycast;*/

}

///
void Enemy::Update(Input* input, bool isTitle) {
	assert(input);
	nowTitle = false;
	nowTitle = !isTitle;

	object_->Update();
	reticle->Update();

	if (input->KeyboardPush(DIK_P) && isDead == false) {
		weapon_->Shot(object_->wtf, reticle->wtf, ENEMY);
	}
	weapon_->Update(input, isSlow);

	FrontFace();
	ColiderUpdate();
}

///
void Enemy::Draw(DirectXCommon* dxCommon) {

	if (isDead == false) {
		Object3d::PreDraw(dxCommon->GetCommandList());
		object_->Draw();
		if (nowTitle) {
			//reticle->Draw();
		}
		/*for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
			coliderPosTest_[i]->Draw();
		}*/
		Object3d::PostDraw();
		if (nowTitle) {
			weapon_->Draw(dxCommon);
		}
	}
}

/// リセットを行う
void Enemy::Reset() {
	delete model_;
	delete weapon_;
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		//delete sphere[i];

	}
}

/// <summary>
/// 撃つ方向に向かせる
/// </summary>
void Enemy::FrontFace() {
	Vector3 faceAngle = { 0,0,0 };
	{
		faceAngle.y = (float)atan2(object_->wtf.position.x - reticle->wtf.position.x, object_->wtf.position.z - reticle->wtf.position.z);
		frontVec_ = faceAngle;
	}

	object_->wtf.rotation = frontVec_;
}

void Enemy::ColiderUpdate() {
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		if (sphere[i]->GetIsHit() == true && sphere[i]->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_PLAYERBULLETS) {
			isDead = true;
		}
	}

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		spherePos[i] = object_->wtf.position;
		sphere[i]->Update();
	}
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		if (isDead) {
			CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
			//delete sphere[i];
		}
	}
}