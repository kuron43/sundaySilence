#include "Bullet.h"

Model* Bullet::bulletModel_ = nullptr;


Bullet::Bullet() {

}
Bullet::~Bullet() {

}
void Bullet::Initialize(Model* model, const Vector3& position, Vector3 move,int team)
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
	SPHERE_COLISSION_NUM = 1;
	sphere.resize(SPHERE_COLISSION_NUM);
	spherePos.resize(SPHERE_COLISSION_NUM);
	//FbxO_.get()->isBonesWorldMatCalc = true;	// ボーンの行列を取得するか
	coliderPosTest_.resize(SPHERE_COLISSION_NUM);

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		sphere[i] = new SphereCollider;
		CollisionManager::GetInstance()->AddCollider(sphere[i]);
		spherePos[i] = Affin::GetWorldTrans(bulletObj_->wtf.matWorld);
		sphere[i]->SetBasisPos(&spherePos[i]);
		sphere[i]->SetRadius(1.0f);
		if (team_ == PLAYER) { // 自機弾
			sphere[i]->SetAttribute(COLLISION_ATTR_PLAYERBULLETS);
		}
		if (team_ == ENEMY) { // 敵弾
			sphere[i]->SetAttribute(COLLISION_ATTR_ENEMIEBULLETS);
		}
		sphere[i]->Update();
		
		
		//test
		/*coliderPosTest_[i] = Object3d::Create();
		//coliderPosTest_[i]->SetModel(Model::LoadFromOBJ("sphere"));
		//coliderPosTest_[i]->wtf.m_Pos = (sphere[i]->center);
		//coliderPosTest_[i]->wtf.scale = Vector3(sphere[i]->GetRadius(), sphere[i]->GetRadius(), sphere[i]->GetRadius());
		//coliderPosTest_[i]->wtf.rotation = (Vector3{ 0,0,0 });
		//coliderPosTest_[i]->Update();*/
	}
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

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		if (sphere[i]->GetIsHit() == true && sphere[i]->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_ENEMIES && team_ == PLAYER) {
			isDead = true;
			CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		}
		if (sphere[i]->GetIsHit() == true && sphere[i]->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_PLAYER && team_ == ENEMY) {
			isDead = true;
			CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		}
		/*if (sphere[i]->GetIsHit() == true && sphere[i]->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_BARRIEROBJECT) {
			isDead = true;
			CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		}*/
		if (isDead == true) {
			CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		}
	}

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		spherePos[i] = Affin::GetWorldTrans(bulletObj_->wtf.matWorld);
		sphere[i]->Update();
	}
}

void Bullet::Draw()
{
	//モデルの描画
	bulletObj_->Draw();

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {

		//coliderPosTest_[i]->Draw();
	}
}

void Bullet::OnColision() {
	isDead = true;
}
