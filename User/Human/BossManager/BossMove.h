#pragma once
#include "IBossState.h"
class BossMove :
    public IBossState
{
	BossMove();
	~BossMove()override;
	/// 更新を行う
	void Update()override;
};

