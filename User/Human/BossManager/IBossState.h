#pragma once

class IBossState
{
protected:

public:

	IBossState();
	virtual ~IBossState();
	/// 更新を行う
	virtual void Update() = 0;
};

