#pragma once
#include "Affin.h"
#include "Input.h"
#include <vector>

class SerialDash
{
public:
	const int MAX_POINTNUM = 5;
	std::vector<Vector3> points;
	Vector3 moveVec[3];
	float dashSpeed;
	int nowPointNum;
	bool isReset;
	bool pointsMax;



public:
	void SetPoint(Vector3* point, Input* input);
	void MakeMoveVec();
	void GoToPoint();
	void Reset();


};

