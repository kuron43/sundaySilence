#pragma once

#include "Affin.h"

class Object3d;
class BaseCollider;

/// <summary>
/// クエリィによる情報を得るための構造体
/// </summary>
struct QueryHit {
	// 衝突相手のオブジェクト
	Object3d* object = nullptr;
	// 衝突相手のコライダー
	BaseCollider* coloder = nullptr;
	// 衝突店
	Vector3 inter;
	// 排斥ベクトル
	Vector3 reject;
};

/// <summary>
/// クエリーで交差を検出した時の動作を規定するクラス
/// </summary>
class QueryCallback
{
public:
	QueryCallback() = default;
	virtual ~QueryCallback() = default;

	/// <summary>
	/// 交差時コールバック
	/// </summary>
	/// <param name="info">交差情報</param>
	/// <returns>クエリーを続けるならtrue、打ち切るならfalseを返す</returns>
	virtual bool OnQueryHit(const QueryHit& info) = 0;
	
};

