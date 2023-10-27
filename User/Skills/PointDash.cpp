/**
 * @file PointDash.cpp
 * @brief
 */
#include "PointDash.h"
#pragma warning(push)
#pragma warning(disable: 4514)
#include <imgui.h>
#pragma warning(pop)

PointDash::~PointDash()
{
	delete ray;
	delete rayHit;
	delete model_;
}

void PointDash::Initialize()
{
	model_ = Model::LoadFromOBJ("pointCircle");
	for (uint32_t i = 0; i < 5; i++) {
		object_[i] = Object3d::Create();
		object_[i]->SetModel(model_);
		object_[i]->Initialize();
		pointActive_[i] = false;
	}
	ray = new RayCollider;
	CollisionManager::GetInstance()->AddCollider(ray);
	rayHit = new RaycastHit;
}

void PointDash::Draw()
{
	for (uint32_t i = 0; i < 5; i++) {
		if (pointActive_[i] == true) {
			object_[i]->Draw();
		}
	}
}

bool PointDash::PointRayUpdate(Vector3 pos, Vector3 ret)
{
	ray->Update();
	for (uint32_t i = 0; i < 5; i++) {

		object_[i]->wtf.rotation.y++;
		object_[i]->Update();
	}

	if (registNum == 0) {
		ray->SetStart(pos);
		ray->SetDir(ret);
		if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
			ImGui::Begin("eneRayHitBarrier");
			ImGui::Text("HIT 1 : dis %f", rayHit->distance);
			ImGui::End();
			return false;
		}
	}
	else if (registNum == 1) {
		ray->SetStart(points[0]);
		ray->SetDir(ret);
		if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
			ImGui::Begin("eneRayHitBarrier");
			ImGui::Text("HIT 2 : dis %f", rayHit->distance);
			ImGui::End();
			return false;
		}
	}
	else if (registNum == 2) {
		ray->SetStart(points[1]);
		ray->SetDir(ret);
		if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
			ImGui::Begin("eneRayHitBarrier");
			ImGui::Text("HIT 3 : dis %f", rayHit->distance);
			ImGui::End();
			return false;
		}
	}
	else if (registNum == 3) {
		ray->SetStart(points[2]);
		ray->SetDir(ret);
		if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
			ImGui::Begin("eneRayHitBarrier");
			ImGui::Text("HIT 4 : dis %f", rayHit->distance);
			ImGui::End();
			return false;
		}
	}
	else if (registNum == 4) {
		ray->SetStart(points[3]);
		ray->SetDir(ret);
		if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
			ImGui::Begin("eneRayHitBarrier");
			ImGui::Text("HIT 5 : dis %f", rayHit->distance);
			ImGui::End();
			return false;
		}
	}
	else {

	}
	return true;
}

void PointDash::SetPoint(Vector3& point, Input* input) {
	Vector3 myPoint;
	myPoint = point;
	if (input) {

	}
	if (registNum == 0) {
		points[0] = point;
		pointActive_[0] = true;
		object_[0]->wtf.position = point;
		registNum = 1;
		return;
	}
	else if (registNum == 1) {
		points[1] = point;
		pointActive_[1] = true;
		object_[1]->wtf.position = point;
		registNum = 2;
	}
	else if (registNum == 2) {
		points[2] = point;
		pointActive_[2] = true;
		object_[2]->wtf.position = point;
		registNum = 3;
	}
	else if (registNum == 3) {
		points[3] = point;
		pointActive_[3] = true;
		object_[3]->wtf.position = point;
		registNum = 4;
	}
	else if (registNum == 4) {
		points[4] = point;
		pointActive_[4] = true;
		object_[4]->wtf.position = point;
		registNum = 5;
	}
	else {

	}

}
void PointDash::MakeMoveVec(Vector3 pos) {
	startPos = pos;
	for (uint32_t i = 0; i <= registNum; i++) {
		if (registNum == 0) {
			resultVec = pos;
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
	for (uint32_t i = 0; i <= registNum; i++) {
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
				easetime = 0;
				pointActive_[0] = false;
				timeEnd = true;
			}
		}
		if (nowPointNum == 1 && time <= easeMaxTime && registNum >= 2) {
			resultVec = Easing::InOutQuintVec3(points[0], points[1], (float)easetime);
			if (time == easeMaxTime - 1) {
				resultVec = points[1];
				nowPointNum = 2;
				time = 1;
				easetime = 0;
				pointActive_[1] = false;
				timeEnd = true;
			}
		}
		if (nowPointNum == 2 && time <= easeMaxTime && registNum >= 3) {
			resultVec = Easing::InOutQuintVec3(points[1], points[2], (float)easetime);
			if (time == easeMaxTime - 1) {
				resultVec = points[2];
				nowPointNum = 3;
				time = 1;
				easetime = 0;
				pointActive_[2] = false;
				timeEnd = true;
			}
		}
		if (nowPointNum == 3 && time <= easeMaxTime && registNum >= 4) {
			resultVec = Easing::InOutQuintVec3(points[2], points[3], (float)easetime);
			if (time == easeMaxTime - 1) {
				resultVec = points[3];
				nowPointNum = 4;
				time = 1;
				easetime = 0;
				pointActive_[3] = false;
				timeEnd = true;
			}
		}
		if (nowPointNum == 4 && time <= 60 && registNum == 5) {
			resultVec = Easing::InOutQuintVec3(points[3], points[4], (float)easetime);
			if (time >= easeMaxTime - 1) {
				resultVec = points[4];
				nowPointNum = 5;
				time = 1;
				easetime = 0;
				pointActive_[4] = false;
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
	for (uint32_t i = 0; i < 5; i++) {
		pointActive_[i] = false;
		object_[i]->wtf.position = Vector3(0, -10, 0);
	}
	registNum = 0;
	isActive = false;
	points.resize(MAX_POINTNUM);
	for (uint32_t i = 0; i < _countof(moveVec); i++) {
		moveVec[i] = Vector3(0, 0, 0);
	}
	//resultVec = Vector3(0, 0, 0);
	time = 0;
	easeSpeed = 0;
	easetime = 0;
}