#pragma once
#include "IPostEffect.h"
#include "PostEffect.h"
#include "vignetteEffect.h"

#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4828)
#pragma warning(disable: 4820)
#include <vector>
#include <memory>

#pragma warning(pop)

class GameScene;

class PostEffectManager
{
public:
	void Initialize(DirectXCommon* dxCommon);
	//void Update();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	void TargetPreDraw(ID3D12GraphicsCommandList* cmdList,GameScene* gameScene);
	//void TargetPostDraw();

	//void EffectMix();
	//void AddEffect(PostEffect* posteffect);
	void UpdateEffect();

public:

private:
	std::unique_ptr<IPostEffect> postEffectMix;

	std::unique_ptr<PostEffect> testFX;
	std::unique_ptr<VignetteEffect> vignetteFX;
};

