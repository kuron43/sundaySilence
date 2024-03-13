#pragma once
#include "PostEffect.h"

#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4828)
#pragma warning(disable: 4820)
#include <vector>
#include <memory>

#pragma warning(pop)

class PostEffectManager
{
public:
	void Initialize();
	void Update();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	void TargetPreDraw(ID3D12GraphicsCommandList* cmdList);
	void TargetPostDraw();

	void EffectMix();
	void AddEffect(PostEffect* posteffect);
	void UpdateEffect();

public:

private:

};

