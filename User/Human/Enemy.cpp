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
		sphere[i]->SetBasisPos(&spherePos[i]);
		sphere[i]->SetRadius(1.0f);
		sphere[i]->Update();
		sphere[i]->SetAttribute(COLLISION_ATTR_ENEMIES);
		////test
		//coliderPosTest_[i] = Object3d::Create();
		//coliderPosTest_[i]->SetModel(model_);
		//coliderPosTest_[i]->wtf.position = sphere[i]->center;
		//coliderPosTest_[i]->wtf.scale = Vector3{ sphere[i]->GetRadius(),sphere[i]->GetRadius() ,sphere[i]->GetRadius() };
		//coliderPosTest_[i]->wtf.rotation = { 0,0,0 };
		//coliderPosTest_[i]->Update();
	}
}

///
void Enemy::Update(Input* input, bool isTitle) {
	assert(input);
	nowTitle = !isTitle;
	object_->Update();
	reticle->Update();
	if (input->KeyboardPush(DIK_P)) {
		weapon_->Shot(object_->wtf, reticle->wtf, ENEMY);
	}
	if (!isTitle) {
		weapon_->Update(input, isSlow);
	}

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		if (sphere[i]->GetIsHit() == true && sphere[i]->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_PLAYERBULLETS) {
			isDead = true;
			CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		}
	}

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		spherePos[i] = object_->wtf.position;
		sphere[i]->Update();
		//coliderPosTest_[i]->Update();
	}
}

///
void Enemy::Draw(DirectXCommon* dxCommon) {

	if (isDead == false) {
		Object3d::PreDraw(dxCommon->GetCommandList());
		object_->Draw();
		if (nowTitle) {
			reticle->Draw();
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
		delete sphere[i];

	}
}