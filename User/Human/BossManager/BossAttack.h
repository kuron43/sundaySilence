#pragma once
#include "IBossState.h"
class BossAttack :
    public IBossState
{
	BossAttack();
	~BossAttack()override;
	/// 更新を行う
	void Update()override;
};

