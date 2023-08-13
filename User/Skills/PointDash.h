#pragma once
#include "Affin.h"
#include "Input.h"
#include <vector>
#include "Easing.h"

class PointDash
{
public:
	const int MAX_POINTNUM = 5;
	std::vector<Vector3> points;
	Vector3 startPos;
	Vector3 moveVec[5];
	float dashSpeed;
	float easeSpeed;
	int nowPointNum;
	int registNum;
	bool isReset;
	bool pointsMax;
	bool moveEnd;
	bool isActive;

	int time;
	float easetime;
	Vector3 resultVec;

public:
	void Update(Vector3 pos);
	void SetPoint(Vector3& point, Input* input);
	void MakeMoveVec(Vector3 pos);
	void GoToPoint();
	void Reset();


};

