#include "ObjectParticle.h"


ObjectParticle* ObjectParticle::Create(
	const Vector3& pos_, Model* model_,const Vector3& velocity_) {
	// インスタンス
	ObjectParticle* instance = new ObjectParticle();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
	instance->Init(pos_, model_, velocity_);

	return instance;
}

void ObjectParticle::Init(
	const Vector3& pos_, Model* model_,const Vector3& velocity_) {
	object3d.reset(object3d->Create());
	object3d->SetModel(model_);
	object3d->transForm.position = pos_;

	object3d-> transForm.scale = { 0.5f, 0.5f, 0.5f };

	velocity = velocity_;

	lifeTimer = 0;

}

void ObjectParticle::Update() {
	if (lifeTimer < lifeTime) {
		lifeTimer++;

		object3d->transForm.position += velocity;

		object3d->transForm.rotation += { 30.0f, 30.0f, 30.0f };

		if (lifeTimer > 40) {
			if (easeTimer < easeTime) {
				easeTimer++;
				object3d->transForm.scale = Easing::OutQuadVec3({ 0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f }, easeTimer / easeTime);
			}
		}
	}
	else {
		isDead = true;
	}

	object3d->Update();
}

void ObjectParticle::Draw() { object3d->Draw(); }

ObjParticleManager* ObjParticleManager::objParticleManager = nullptr;

void ObjParticleManager::Init() {
	// キューブ生成
	//model = ModelManager::GetInstance()->GetModels("Cube");

}

void ObjParticleManager::Update() {
	objParticles.remove_if(
		[](std::unique_ptr<ObjectParticle>& objParticle) { return objParticle->GetIsDead(); });

	for (std::unique_ptr<ObjectParticle>& objParticle : objParticles) {
		objParticle->Update();
	}
}

void ObjParticleManager::Draw() {
	for (std::unique_ptr<ObjectParticle>& objParticle : objParticles) {
		objParticle->Draw();
	}
}

void ObjParticleManager::SetExp(const Vector3& pos_) {
	std::unique_ptr<ObjectParticle> newParticle;
	for (size_t i = 0; i < 40; i++) {
		// 生成
		newParticle.reset(ObjectParticle::Create(
			pos_, model,{ MathUtility::Randoms::GetRandFloat(-1.0f, 1.0f), MathUtility::Randoms::GetRandFloat(-1.0f, 1.0f),
			 MathUtility::Randoms::GetRandFloat(-1.0f, 1.0f) }));
		// 出力
		objParticles.push_back(std::move(newParticle));
	}
}

void ObjParticleManager::SetSmallExp(const Vector3& pos_) {
	std::unique_ptr<ObjectParticle> newParticle;
	for (size_t i = 0; i < 10; i++) {
		// 生成
		newParticle.reset(ObjectParticle::Create(
			pos_, model,{ MathUtility::Randoms::GetRandFloat(-0.25f, 0.25f), MathUtility::Randoms::GetRandFloat(-0.25f, 0.25f),
			 MathUtility::Randoms::GetRandFloat(-0.25f, 0.25f) }));
		// 出力
		objParticles.push_back(std::move(newParticle));
	}
}

ObjParticleManager* ObjParticleManager::GetInstance() {
	static ObjParticleManager instance;
	return &instance;
}

void ObjParticleManager::Delete() { delete objParticleManager; }