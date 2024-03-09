/**
 * @file BulletManager.h
 * @brief
 */
#pragma once
#include "Bullet.h"

#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4828)
#pragma warning(disable: 4820)
#include <forward_list>
//#include <vector>
#include <memory>

#pragma warning(pop)

// 弾管理クラス
class BulletManager
{
public:
	static BulletManager* GetInstance();
public:
	//弾の追加
	inline void AddBullet(std::unique_ptr<Bullet> bullet)
	{
		bullets.push_back(std::move(bullet));
	}

	//// 弾の削除
	//inline void RemoveBullet(std::unique_ptr<Bullet> bullet)
	//{
	//	bullets.erase(bullets[], bullets);
	//}
	// 弾のオールクリア
	inline void AllClearBullet()
	{
		bullets.clear();
	}

	static void SetSpeed(float speed) { speed_ = speed; }
	void Update();
	//void DeadUpdate();
	void Draw();

private:
	static float speed_;

	BulletManager() = default;
	BulletManager(const BulletManager&) = delete;
	BulletManager& operator= (const BulletManager&) = delete;

	~BulletManager() {
		AllClearBullet();
	};

	//弾のリスト
	std::list<std::unique_ptr<Bullet>> bullets;
};

