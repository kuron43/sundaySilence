#pragma once

class Input;
class DirectXCommon;

class Weapon
{
protected:
	

public:
	Weapon();
	virtual ~Weapon();

	/// 更新を行う
	virtual void Initialize() = 0;

	/// 更新を行う
	virtual void Update(Input* input,bool isSlow) = 0;

	/// 描画を行う
	virtual void Draw(DirectXCommon* dxCommon) = 0;

	/// リセットを行う
	virtual void Reset() = 0;


};

