#include "EndScene.h"
#include "SceneManager.h"

#include "TitleScene.h"

EndScene::EndScene(SceneManager* controller) {
	_controller = controller;
}
EndScene::~EndScene() {
	delete particleManager;

}

void EndScene::Initialize(DirectXCommon* dxCommon) {
	// パーティクル生成
	particleManager = ParticleManager::Create();
	particleManager->LoadTexture("1.png");
	particleManager->Update();
}

void EndScene::Update(Input* input) {
	if (input->TriggerKey(DIK_SPACE)) {
		_controller->ChangeScene(new TitleScene(_controller));
	}

	particleManager->Update();

	// パーティクル起動( P 押し)
	{
		if (input->TriggerKey(DIK_P)) {
			//パーティクル範囲
			for (int j = 0; j < 50; j++) {
				//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
				const float rnd_pos = 0.03f;
				//const float rnd_posX = 1.0f;
				Vector3 pos{};
				pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.z += ((float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f) + 10;

				//速度
				//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
				const float rnd_vel = 0.5f;
				Vector3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				//重力に見立ててYのみ[-0.001f,0]でランダムに分布
				const float rnd_acc = -0.01f;
				const float rnd_acc_v = -0.01f;
				Vector3 acc{};
				acc.x = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
				acc.y = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
				//acc.z = (float)rand() / RAND_MAX * rnd_acc;

				//追加
				particleManager->Add(50, pos, vel, acc, 1.0f, 0.0f);
			}
		}
	}

}

void EndScene::Draw(DirectXCommon* dxCommon) {

	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(dxCommon->GetCommandList());

	//// 3Dオブクジェクトの描画
	particleManager->Draw();

	// 3Dオブジェクト描画後処理
	ParticleManager::PostDraw();

}