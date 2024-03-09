#pragma once
#include "PostEffect.h"

#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4828)
#pragma warning(disable: 4820)
#include <forward_list>
#include <memory>

#pragma warning(pop)

class PostEffectManager
{
public:
	void Initialize();
	void EffectMix();
	void AddEffect();
	void UpdateEffect();
	void Draw();

public:

private:

};

