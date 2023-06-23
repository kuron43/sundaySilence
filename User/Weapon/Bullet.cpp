#include "Bullet.h"

Model* Bullet::bulletModel_ = nullptr;


Bullet::Bullet() {

}
Bullet::~Bullet() {

}
void Bullet::Initialize(Model* model, const Vector3& position, Vector3 move)
{
	//NULLチェック
	assert(model);

	bulletObj_ = std::make_unique<Object3d>();
	bulletObj_->Initialize();
	bulletObj_->SetModel(model);
	moveVec = move;

	bulletObj_->wtf.scale = Vector3(0.8f, 0.8f, 0.8f);
	bulletObj_->wtf.position = position;
}

void Bullet::Update(float speed)
{

	bulletObj_->wtf.position += (moveVec * speed);
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
