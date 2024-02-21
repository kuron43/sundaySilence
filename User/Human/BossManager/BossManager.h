#pragma once
#include "Human.h"

class Boss;
class BossManager
{
public:
	enum BoFbxAnim {
		BoF_REST = 0,
		BoF_MOVE,
		BOF_ATACK,
	};
	enum BoAction {
		BoA_WAIT = 0,
		BoA_MOVE,
		BOA_ATACK,
	};
private:
	Boss* boss_;

	uint32_t patNum_;

public:
	void SetBoss(Boss* boss) { boss_ = boss; }
	void Update(uint32_t pattNum);
};

