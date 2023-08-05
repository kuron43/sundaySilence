#include "PointDash.h"

void PointDash::Update(Vector3 pos)
{

}

void PointDash::SetPoint(Vector3& point, Input* input) {
	if (input) {

	}
	if (registNum == 0) {
		points[0] = point;
		registNum = 1;
		isActive = true;
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
}
void PointDash::GoToPoint() {

}
void PointDash::Reset() {
	points.clear();
	registNum = 0;
	isActive = false;
	points.resize(MAX_POINTNUM);
	for (int i = 0; i <= _countof(moveVec); i++) {
		moveVec[i] = Vector3(0,0,0);
	}
}