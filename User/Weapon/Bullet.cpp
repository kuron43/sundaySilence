/**
 * @file Bullet.cpp
 * @brief
 */
#include "Bullet.h"

#include "ImGui.h"

Model* Bullet::bulletModel_ = nullptr;


Bullet::Bullet() {

}
Bullet::~Bullet() {
	if (sphere) {
		CollisionManager::GetInstance()->RemoveCollider(sphere);
		delete sphere;
	}
	if (bulletObj_) {
		delete bulletObj_;
	}
}
void Bullet::Initialize(Model* model, const Vector3& position, Vector3 move, uint32_t team)
{
	//NULLチェック
	assert(model);
	team_ = team;
	moveVec = move;

	bulletObj_ = Object3d::Create();
	bulletObj_->SetModel(model);

	bulletObj_->wtf.scale = Vector3(0.8f, 0.8f, 0.8f);
	bulletObj_->wtf.position = position;
	timeCount = 0;
	isDead = false;
	if (team_ == PLAYER) {
		bulletObj_->SetColor({ 0,1,1,1 }); // カラー?RGB の順番
	}if (team_ == ENEMY) {
		bulletObj_->SetColor({ 1,1,0,1 });
	}

	//当たり判定用
	sphere = new SphereCollider;
	CollisionManager::GetInstance()->AddCollider(sphere);
	spherePos = Affin::GetWorldTrans(bulletObj_->wtf.matWorld);
	sphere->SetObject3d(bulletObj_);
	//sphere->SetBasisPos(&spherePos[i]);
	sphere->SetRadius(0.8f);
	sphere->Update();
	sphere->SetAttribute(COLLISION_ATTR_PLAYERBULLETS);
	if (team_ == PLAYER) { // 自機弾
	}
	else if (team_ == ENEMY) { // 敵弾
		sphere->SetAttribute(COLLISION_ATTR_ENEMIEBULLETS);
	}
	else {
		sphere->SetAttribute(COLLISION_ATTR_UNKNOWN);
	}


	////test
	//coliderPosTest_ = Object3d::Create();
	//coliderPosTest_->SetModel(model);
	//coliderPosTest_->wtf.position = (sphere->center);
	//coliderPosTest_->wtf.scale = Vector3(sphere->GetRadius(), sphere->GetRadius(), sphere->GetRadius());
	//coliderPosTest_->wtf.rotation = (Vector3{ 0,0,0 });
	//coliderPosTest_->Update();
}

void Bullet::Update(float speed)
{
	timeCount++;
	if (timeCount >= DEATH_TIME) {
		Dead();
	}
	bulletObj_->wtf.position += (moveVec * speed);
	//行列の再計算
	bulletObj_->Update();

	if (sphere->GetIsHit() == true) {
		if (sphere->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_BARRIEROBJECT && team_ == PLAYER ||
			sphere->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_BARRIEROBJECT && team_ == ENEMY) {
			isDead = true;
		}
		if (sphere->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_ENEMIES && team_ == PLAYER) {
			isDead = true;
		}
		if (sphere->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_PLAYER && team_ == ENEMY) {
			isDead = true;
		}
	}
	sphere->Update();

	//ImGui::Begin("bullet");
	//ImGui::SetWindowPos({ 600,50 });
	//ImGui::SetWindowSize({500.0f,200.0f});
	//ImGui::InputFloat4("color", &bulletObj_->color_.x);
	//ImGui::End();
}

void Bullet::DeadUpdate() {
	if (isDead == true) {
		CollisionManager::GetInstance()->RemoveCollider(sphere);
		//delete sphere;
	}
}

void Bullet::Draw()
{
	//coliderPosTest_->Draw();
	//モデルの描画
	bulletObj_->Draw();
}

void Bullet::OnColision() {
	isDead = true;
}

bool Bullet::IsDead()
{
	return isDead;
}
