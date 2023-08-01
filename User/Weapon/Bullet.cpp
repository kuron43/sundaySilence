#include "Bullet.h"

Model* Bullet::bulletModel_ = nullptr;


Bullet::Bullet() {

}
Bullet::~Bullet() {

}
void Bullet::Initialize(Model* model, const Vector3& position, Vector3 move, int team)
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
		Vector4 color(0.0f, 0.0f, 1.0f, 1.0f);  // カラーなぜかARGB の順番
		bulletObj_->SetColor(color);
	}if (team_ == ENEMY) {
		Vector4 color(0.0f, 1.0f, 1.0f, 0.0f);
		bulletObj_->SetColor(color);
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


	//test
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
	if (timeCount >= deathTime) {
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
	if (isDead == true) {
		assert(sphere);
	}

	sphere->Update();
}

void Bullet::DeadUpdate() {
	if (isDead == true) {
		CollisionManager::GetInstance()->RemoveCollider(sphere);
		//delete sphere;
	}
}

void Bullet::Draw()
{
	if (!isDead) {
		//モデルの描画
		bulletObj_->Draw();
		//coliderPosTest_->Draw();
	}
}

void Bullet::OnColision() {
	isDead = true;
}
