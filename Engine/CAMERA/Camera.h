#pragma once

//#include <DirectXMath.h>

#include "Vector3.h"
#include "Matrix4.h"
#include "Affin.h"

/// <summary>
/// カメラ基本機能
/// </summary>
class Camera
{

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	Camera(int window_width, int window_height);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Camera() = default;

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	void UpdateViewMatrix();

	/// <summary>
	/// 射影行列を更新
	/// </summary>
	void UpdateProjectionMatrix();

	/// <summary>
	/// ビュー行列の取得
	/// </summary>
	/// <returns>ビュー行列</returns>
	inline const Matrix4& GetViewMatrix() {
		return matView;
	}

	/// <summary>
	/// 射影行列の取得
	/// </summary>
	/// <returns>射影行列</returns>
	inline const Matrix4& GetProjectionMatrix() {
		return matProjection;
	}

	/// <summary>
	/// ビュー射影行列の取得
	/// </summary>
	/// <returns>ビュー射影行列</returns>
	inline const Matrix4& GetViewProjectionMatrix() {
		return matViewProjection;
	}

	/// <summary>
	/// ビルボード行列の取得
	/// </summary>
	/// <returns>ビルボード行列</returns>
	inline const Matrix4& GetBillboardMatrix() {
		return matBillboard;
	}

	/// <summary>
	/// 視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	inline const Vector3& GetEye() {
		return eye;
	}

	/// <summary>
	/// 視点座標の設定
	/// </summary>
	/// <param name="eye">座標</param>
	inline void SetEye(Vector3 eye) {
		this->eye = eye; viewDirty = true;
	}

	/// <summary>
	/// 注視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	inline const Vector3& GetTarget() {
		return target;
	}

	/// <summary>
	/// 注視点座標の設定
	/// </summary>
	/// <param name="target">座標</param>
	inline void SetTarget(Vector3 target) {
		this->target = target; viewDirty = true;
	}

	/// <summary>
	/// 上方向ベクトルの取得
	/// </summary>
	/// <returns>上方向ベクトル</returns>
	inline const Vector3& GetUp() {
		return up;
	}

	/// <summary>
	/// 上方向ベクトルの設定
	/// </summary>
	/// <param name="up">上方向ベクトル</param>
	inline void SetUp(Vector3 up) {
		this->up = up; viewDirty = true;
	}

	// sensor
	inline const float& GetSensor() {
		return sensor;
	}
	inline void SetSensor(float sensor) {
		this->sensor = sensor; viewDirty = true;
	}
	// FL
	inline const float& GetForcalLengs() {
		return focalLengs;
	}
	inline void SetFocalLengs(float focalLengs) {
		this->focalLengs = focalLengs; viewDirty = true;
	}


	/// <summary>
	/// ベクトルによる視点移動
	/// </summary>
	/// <param name="move">移動量</param>
	void MoveEyeVector(const Vector3& move);

	/// <summary>
	/// ベクトルによる移動
	/// </summary>
	/// <param name="move">移動量</param>
	void MoveVector(const Vector3& move);

	float FieldOfViewY();

protected: // メンバ変数
	// ビュー行列
	Matrix4 matView = Affin::matUnit();
	// ビルボード行列
	Matrix4 matBillboard = Affin::matUnit();
	// Y軸回りビルボード行列
	Matrix4 matBillboardY = Affin::matUnit();
	// 射影行列
	Matrix4 matProjection = Affin::matUnit();
	// ビュー射影行列
	Matrix4 matViewProjection = Affin::matUnit();
	// ビュー行列ダーティフラグ
	bool viewDirty = false;
	// 射影行列ダーティフラグ
	bool projectionDirty = false;
	// 視点座標
	Vector3 eye = {0, 0, -1};
	// 注視点座標
	Vector3 target = {0, 0, 0};
	// 上方向ベクトル
	Vector3 up = {0, 1, 0};
	// アスペクト比
	float aspectRatio = 1.0f;

	float focalLengs = 50 ;
	float sensor = 35;
};

