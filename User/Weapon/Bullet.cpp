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

	bulletObj_ = Object3d::Create();
	bulletObj_->SetModel(model);
	moveVec = move;

	bulletObj_->wtf.scale = Vector3(0.8f, 0.8f, 0.8f);
	bulletObj_->wtf.position = position;
	timeCount = 0;
	isDead = false;
	team_ = team;
	if (team_ == 0) {
		Vector4 color(0.0f, 0.0f, 0.0f, 1.0f);  // カラーなぜかARGB の順番
		bulletObj_->SetColor(color);
	}if (team_ == 1) {
		Vector4 color(0.0f, 0.0f, 1.0f, 0.0f);
		bulletObj_->SetColor(color);
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
}

void Bullet::Draw()
{
	//モデルの描画
	bulletObj_->Draw();
}

void Bullet::OnColision() {
	isDead = true;
}
