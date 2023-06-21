#include "Bullet.h"

Model* Bullet::bulletModel_ = nullptr;

void Bullet::Initialize( const Vector3& position, Vector3 move)
{
	//NULLチェック
	assert(bulletModel_);

	bulletObj_->Initialize();
	bulletObj_->wtf.Initialize();
	bulletObj_->SetModel(bulletModel_);
	moveVec = move;

	bulletObj_->wtf.scale = Vector3(0.5f, 0.5f, 0.5f);
	bulletObj_->wtf.position = position;
}

void Bullet::Update()
{

	bulletObj_->wtf.position += (moveVec * 1.5f);
	//行列の再計算
	bulletObj_->Update();
}

void Bullet::Draw()
{
	//モデルの描画
	bulletObj_->Draw();
}

void Bullet::OnColision() {
	isDead = true;
}
