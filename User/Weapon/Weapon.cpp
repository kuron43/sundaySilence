#include "Weapon.h"
#include <cassert>

Weapon::Weapon() {

}
Weapon::~Weapon() {

}
Weapon* Weapon::Create()
{
	return this;
}
/// 更新を行う
bool Weapon::Initialize() {

	return true;
}

/// 更新を行う
void Weapon::Update(Input* input, bool isSlow) {
	assert(input);
	if (isSlow == false) {

	}
	if (input) {

	}
}

/// 描画を行う
void Weapon::Draw(DirectXCommon* dxCommon) {
	assert(dxCommon);
	dxCommon->GetDevice();
}

/// リセットを行う
void Weapon::Reset() {

}

/// <summary>
///  発射を行う
/// </summary>
/// <param name="player"></param>
/// <param name="reticle"></param>
/// <param name="team">0 = 敵：1 ＝ 自</param>
void Weapon::Shot(Transform& player, Transform& reticle, uint32_t team) {
	player;
	reticle;
	team;
}