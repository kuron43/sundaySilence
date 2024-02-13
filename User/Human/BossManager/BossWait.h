#pragma once
#include "IBossState.h"
class BossWait :
	public IBossState
{
public:
	BossWait();
	~BossWait()override;
	/// 更新を行う
	void Update()override;
};

