#include "PostEffectManager.h"
#include "GameScene.h"

void PostEffectManager::Initialize(DirectXCommon* dxCommon)
{
	vignetteFX = std::make_unique<VignetteEffect>();
	vignetteFX->Initialize(dxCommon, L"Vignette");

	postEffectMix = std::make_unique<IPostEffect>();
	postEffectMix->Initialize(dxCommon, L"IPostEffect");

	testFX = std::make_unique<PostEffect>();
	testFX->Initialize(dxCommon, L"PostEffect");
	testFX->SetKernelSize(3);
	testFX->SetRadialBlur(Vector2(WinApp::window_width / 2, WinApp::window_height / 2), 0.1f, 10);
	testFX->SetShadeNumber(0);
}

void PostEffectManager::Draw(ID3D12GraphicsCommandList* cmdList)
{
	postEffectMix->Draw(cmdList);
}

void PostEffectManager::TargetPreDraw(ID3D12GraphicsCommandList* cmdList,GameScene* gameScene)
{
	testFX->PreDrawScene(cmdList);
	gameScene->Draw();
	testFX->PostDrawScene();

	vignetteFX->PreDrawScene(cmdList);
	gameScene->Draw();
	vignetteFX->PostDrawScene();


	//////////////
	postEffectMix->PreDrawScene(cmdList, 0);
	testFX->Draw(cmdList);
	postEffectMix->PostDrawScene(0);

	postEffectMix->PreDrawScene(cmdList, 1);
	vignetteFX->Draw(cmdList);
	postEffectMix->PostDrawScene(1);

}

void PostEffectManager::UpdateEffect()
{
}
