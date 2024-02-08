#pragma once

class IBossState
{
protected:

public:

	IBossState();
	virtual ~IBossState();
	/// シーンの更新を行う
	virtual void Update() = 0;

	/// シーンの描画を行う
	virtual void Draw() = 0;
};

