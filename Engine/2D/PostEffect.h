#pragma once
#include "Sprite.h"

class PostEffect:
	public Sprite
{
public:
	PostEffect();
	~PostEffect();

	void Draw(ID3D12GraphicsCommandList* cmdList)
};

