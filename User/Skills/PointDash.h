#pragma once
#include "Affin.h"
#include "Input.h"
#include <vector>

class PointDash
{
public:
	const int MAX_POINTNUM = 5;
	std::vector<Vector3> points;
	Vector3 moveVec[5];
	float dashSpeed;
	int nowPointNum;
	int registNum;
	bool isReset;
	bool pointsMax;
	bool moveEnd;
	bool isActive;


public:
	void Update(Vector3 pos);
	void SetPoint(Vector3& point, Input* input);
	void MakeMoveVec(Vector3 pos);
	void GoToPoint();
	void Reset();


};

