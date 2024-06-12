#include "ObjectParticle.h"


ObjectParticle* ObjectParticle::Create(
	const Vector3& pos_, Model* model_, const Vector3& velocity_, float scale, Vector4 color) {
	// インスタンス
	ObjectParticle* instance = new ObjectParticle();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
	instance->Init(pos_, model_, velocity_, scale, color);

	return instance;
}

void ObjectParticle::Init(
	const Vector3& pos_, Model* model_, const Vector3& velocity, float scale, Vector4 color) {
	object_.reset(object_->Create());
	object_->SetModel(model_);
	object_->SetColor(color);
	object_->transForm.position = pos_;
	object_->transForm.scale = { scale,scale,scale };

	velocity_ = velocity;

	lifeTimer = 0;

}

void ObjectParticle::Update() {
	if (lifeTimer < MAXLIFETIME) {
		lifeTimer++;

		object_->transForm.position += velocity_;

		object_->transForm.rotation += { 30.0f, 30.0f, 30.0f };

		if (lifeTimer > MAXLIFETIME - MAXEASETIME) {
			if (easeTimer < MAXEASETIME) {
				easeTimer++;
				object_->transForm.scale = Easing::OutQuadVec3({ 0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f }, easeTimer / MAXEASETIME);
			}
		}
	}
	else {
		isDead = true;
	}

	object_->Update();
}

void ObjectParticle::Draw() { object_->Draw(); }

void ObjParticleManager::Init(Model* model) {
	model_ = model;

}

void ObjParticleManager::Update() {
	objParticles_.remove_if(
		[](std::unique_ptr<ObjectParticle>& objParticle) { return objParticle->GetIsDead(); });

	for (std::unique_ptr<ObjectParticle>& objParticle : objParticles_) {
		objParticle->Update();
	}
}

void ObjParticleManager::Draw() {
	for (std::unique_ptr<ObjectParticle>& objParticle : objParticles_) {
		objParticle->Draw();
	}
}

void ObjParticleManager::SetAnyExp(const Vector3& pos_, Vector2 velocityMinMax, size_t volume, float scale, Vector4 color) {
	std::unique_ptr<ObjectParticle> newParticle;
	float min, max;
	min = velocityMinMax.x;
	max = velocityMinMax.y;
	for (size_t i = 0; i < volume; i++) {
		// 生成
		newParticle.reset(ObjectParticle::Create(
			pos_, model_, {
				MathUtility::Randoms::GetRandFloat(min, max),
				MathUtility::Randoms::GetRandFloat(min, max),
				MathUtility::Randoms::GetRandFloat(min, max) },
				scale, color
				));
		// 出力
		objParticles_.push_back(std::move(newParticle));
	}
}

void ObjParticleManager::SetAnyExp(ParticlePreset preset)
{
	std::unique_ptr<ObjectParticle> newParticle;
	float min, max;
	min = preset.velocityMinMax.x;
	max = preset.velocityMinMax.y;
	for (size_t i = 0; i < preset.volume; i++) {
		// 生成
		newParticle.reset(ObjectParticle::Create(
			preset.pos_, model_, {
				MathUtility::Randoms::GetRandFloat(min, max),
				MathUtility::Randoms::GetRandFloat(min, max),
				MathUtility::Randoms::GetRandFloat(min, max) },
				preset.scale, preset.color
				));
		// 出力
		objParticles_.push_back(std::move(newParticle));
	}
}

ObjParticleManager* ObjParticleManager::GetInstance() {
	static ObjParticleManager instance;
	return &instance;
}