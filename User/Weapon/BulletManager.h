#pragma once
#include "Bullet.h"

#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4828)
#include <forward_list>
#include <d3d12.h>

#pragma warning(pop)

class BulletManager
{
public:
	static BulletManager* GetInstance();
public:
	//弾の追加
	inline void AddBullet(Bullet* bullet)
	{
		bullets.push_front(bullet);
	}

	// 弾の削除
	inline void RemoveBullet(Bullet* bullet)
	{
		bullets.remove(bullet);
	}

	static void SetSpeed(float speed) { speed_ = speed; }
	void Update();
	void Draw();

private:
	static float speed_;

	BulletManager() = default;
	BulletManager(const BulletManager&) = delete;
	~BulletManager() = default;
	BulletManager& operator= (const BulletManager&) = delete;

	//弾のリスト
	std::list<Bullet*> bullets;
};

