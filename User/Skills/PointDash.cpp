#include "PointDash.h"
#include "imgui.h"

void PointDash::Update(Vector3 pos)
{
	Vector3 a = pos;
	a.x++;
}

void PointDash::SetPoint(Vector3& point, Input* input) {
	Vector3 myPoint;
	myPoint = point;
	if (input) {

	}

		if (registNum == 0) {
			points[0] = point;
			registNum = 1;
		}
		else if (registNum == 1) {
			points[1] = point;
			registNum = 2;
		}
		else if (registNum == 2) {
			points[2] = point;
			registNum = 3;
		}
		else if (registNum == 3) {
			points[3] = point;
			registNum = 4;
		}
		else if (registNum == 4) {
			points[4] = point;
			registNum = 5;
		}
		else {

		}
	
}
void PointDash::MakeMoveVec(Vector3 pos) {
	startPos = pos;
	for (int i = 0; i < registNum; i++) {
		if (registNum == 0) {
			break;
		}
		else if (i == 0) {
			moveVec[0] = pos - points[0];
		}
		else if (0 < i && i < 5)
		{
			moveVec[i] = Vector3(points[i - 1] - points[i]);
		}
		else {

		}
	}
	for (int i = 0; i <= registNum; i++) {
		moveVec[i].nomalize();

	}
	isActive = true;
	nowPointNum = 0;
}
void PointDash::GoToPoint() {
	timeEnd = false;
	if (isActive) {
		time++;

		easetime = (float)time / easeMaxTime;
		if (nowPointNum == 0 && time <= easeMaxTime && registNum >= 1) {
			resultVec = Easing::InOutQuintVec3(startPos, points[0], (float)easetime);
			if (time == easeMaxTime - 1) {
				nowPointNum = 1;
				time = 1;
				timeEnd = true;
			}
		}
		if (nowPointNum == 1 && time <= easeMaxTime && registNum >= 2) {
			resultVec = Easing::InOutQuintVec3(points[0], points[1], (float)easetime);
			if (time == easeMaxTime - 1) {
				resultVec = points[1];
				nowPointNum = 2;
				time = 1;
				timeEnd = true;
			}
		}
		if (nowPointNum == 2 && time <= easeMaxTime && registNum >= 3) {
			resultVec = Easing::InOutQuintVec3(points[1], points[2], (float)easetime);
			if (time == easeMaxTime - 1) {
				resultVec = points[2];
				nowPointNum = 3;
				time = 1;
				timeEnd = true;
			}
		}
		if (nowPointNum == 3 && time <= easeMaxTime && registNum >= 4) {
			resultVec = Easing::InOutQuintVec3(points[2], points[3], (float)easetime);
			if (time == easeMaxTime - 1) {
				resultVec = points[3];
				nowPointNum = 4;
				time = 1;
				timeEnd = true;
			}
		}
		if (nowPointNum == 4 && time <= 60 && registNum == 5) {
			resultVec = Easing::InOutQuintVec3(points[3], points[4], (float)easetime);
			if (time >= easeMaxTime - 1) {
				resultVec = points[4];
				nowPointNum = 5;
				time = 1;
				timeEnd = true;
			}
		}
	}
	if (nowPointNum == registNum) {
		isActive = false;
		timeEnd = false;
		Reset();
	}
	
}
void PointDash::Reset() {
	points.clear();
	registNum = 0;
	isActive = false;
	points.resize(MAX_POINTNUM);
	for (int i = 0; i < _countof(moveVec); i++) {
		moveVec[i] = Vector3(0, 0, 0);
	}
	//resultVec = Vector3(0, 0, 0);
	time = 0;
	easeSpeed = 0;
	easetime = 0;
}