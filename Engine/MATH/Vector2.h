#pragma once
class Vector2
{
public:
	float x;	//x成分
	float y;	//y成分

public:
	//　コンストラクタ
	Vector2();					//零ベクトルとして生成
	Vector2(float x, float y);		//x成分、ｙ成分を指定しての生成
	void Init();
	void Init(float num);

	//　メンバ関数
	float length() const;				//ノルム（長さ）を求める
	Vector2& normalize();				//正規化する
	float dot(const Vector2& v) const;	//内積を求める
	float cross(const Vector2& v) const;//外積を求める

	//　単項演算子オーバーロード
	Vector2 operator+() const;
	Vector2 operator-() const;

	//　代入演算子オーバーロード
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
};

//二項演算子オーバーロード
//※いろんな引数（引数の方と順序）のパターンに対応するため、以下のように準備している
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);
