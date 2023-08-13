#include "PointDash.h"
#include "imgui.h"

void PointDash::Update(Vector3 pos)
{
	Vector3 a = pos;
	a.x++;
}

void PointDash::SetPoint(Vector3& point, Input* input) {
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
	if (isActive) {
		time++;
		
		easetime = (float)time / 30;
		if (nowPointNum == 0 && time <=30) {
			resultVec = Easing::OutQuintVec3(startPos, points[0], (float)easetime);
			easeSpeed = Easing::OutQuadFloat(0.0f, 1.0f, (float)easetime);
			if (time == 30) {
				nowPointNum = 1;
				time = 0;
			}
		}
		if (nowPointNum == 1 && time <= 30) {
			resultVec = Easing::OutQuintVec3(points[0], points[1], (float)easetime);
			easeSpeed = Easing::OutQuadFloat(0.0f, 1.0f, (float)easetime);
			if (time == 30) {
				nowPointNum = 2;
				time = 0;
			}
		}
		if (nowPointNum == 2 && time <= 30) {
			resultVec = Easing::OutQuintVec3(points[1], points[2], (float)easetime);
			easeSpeed = Easing::OutQuadFloat(0.0f, 1.0f, (float)easetime);
			if (time == 30) {
				nowPointNum = 3;
				time = 0;
			}
		}
		if (nowPointNum == 3 && time <= 30) {
			resultVec = Easing::OutQuintVec3(points[2], points[3], (float)easetime);
			easeSpeed = Easing::OutQuadFloat(0.0f, 1.0f, (float)easetime);
			if (time == 30) {
				nowPointNum = 4;
				time = 0;
			}
		}
		if (nowPointNum == 4 && time <= 30) {
			resultVec = Easing::OutQuintVec3(points[3], points[4], (float)easetime);
			easeSpeed = Easing::OutQuadFloat(0.0f, 1.0f, (float)easetime);
			if (time >= 29) {
				nowPointNum = 5;
				isActive = false;
			}
		}
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
	resultVec = Vector3(0, 0, 0);
	time = 0;
	easeSpeed = 0;
	easetime = 0;
}