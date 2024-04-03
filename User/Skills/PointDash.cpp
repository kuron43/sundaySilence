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
	for (uint32_t i = 0; i < 5; i++) {
		delete object_[i];
	}
	points.clear();
	delete debugModel_;
}

void PointDash::Initialize()
{
	debugModel_ = Model::LoadFromOBJ("cube");
	debugOBJ_ = std::make_unique<Object3d>();
	debugOBJ_->Initialize();
	debugOBJ_->SetModel(debugModel_);

	model_ = Model::LoadFromOBJ("pointCircle");
	for (uint32_t i = 0; i < 5; i++) {
		object_[i] = Object3d::Create();
		object_[i]->SetModel(model_);
		object_[i]->Initialize();
		object_[i]->wtf.scale = Vector3(1.5f, 1.5f, 1.5f);
		pointActive_[i] = false;
	}

	particle_ = std::make_unique<ParticleManager>();
	particle_->Initialize();
	particle_->LoadTexture("lightgray.png");
	particle_->Update();
	onPatTime_ = 0;
	onPat_ = false;

	ray = new RayCollider;
	CollisionManager::GetInstance()->AddCollider(ray);
	rayHit = new RaycastHit;
}

void PointDash::Draw(DirectXCommon* dxCommon)
{
	Object3d::PreDraw(dxCommon->GetCommandList());

	for (uint32_t i = 0; i < 5; i++) {
		if (pointActive_[i] == true) {
			object_[i]->Draw();
		}
	}
	debugOBJ_->Draw();
	Object3d::PostDraw();
	particle_->Draw();
}

bool PointDash::PointRayUpdate(Vector3 pos, Vector3 ret)
{
	particle_->Update();
	ray->Update();

	for (uint32_t i = 0; i < 5; i++) {
		object_[i]->wtf.rotation.y += registNum;
		object_[i]->Update();
	}

	// ポイントダッシュ間のライン計算処理
	{
		//float debugLineAngle;
		//Vector3 debugPos;
		//switch (registNum)
		//{
		//case 0:
		//	debugLineAngle = (float)atan2(ret.x - pos.x, ret.z - pos.z);
		//	debugOBJ_->wtf.rotation.y = debugLineAngle;
		//	debugOBJ_->wtf.scale.z = (pos - ret).length() / 2;
		//	debugOBJ_->wtf.position = debugPos.lerp(pos, ret, 0.5f);
		//	break;
		//case 1:
		//	debugLineAngle = (float)atan2(ret.x - object_[0]->wtf.position.x, ret.z - object_[0]->wtf.position.z);
		//	debugOBJ_->wtf.rotation.y = debugLineAngle;
		//	debugOBJ_->wtf.scale.z = (object_[0]->wtf.position - ret).length() / 2;
		//	debugOBJ_->wtf.position = debugPos.lerp(object_[0]->wtf.position, ret, 0.5f);
		//	break;
		//case 2:
		//	debugLineAngle = (float)atan2(ret.x - object_[1]->wtf.position.x, ret.z - object_[1]->wtf.position.z);
		//	debugOBJ_->wtf.rotation.y = debugLineAngle;
		//	debugOBJ_->wtf.scale.z = (object_[1]->wtf.position - ret).length() / 2;
		//	debugOBJ_->wtf.position = debugPos.lerp(object_[1]->wtf.position, ret, 0.5f);
		//	break;
		//case 3:
		//	debugLineAngle = (float)atan2(ret.x - object_[2]->wtf.position.x, ret.z - object_[2]->wtf.position.z);
		//	debugOBJ_->wtf.rotation.y = debugLineAngle;
		//	debugOBJ_->wtf.scale.z = (object_[2]->wtf.position - ret).length() / 2;
		//	debugOBJ_->wtf.position = debugPos.lerp(object_[2]->wtf.position, ret, 0.5f);
		//	break;
		//case 4:
		//	debugLineAngle = (float)atan2(ret.x - object_[3]->wtf.position.x, ret.z - object_[3]->wtf.position.z);
		//	debugOBJ_->wtf.rotation.y = debugLineAngle;
		//	debugOBJ_->wtf.scale.z = (object_[3]->wtf.position - ret).length() / 2;
		//	debugOBJ_->wtf.position = debugPos.lerp(object_[3]->wtf.position, ret, 0.5f);
		//	break;
		//default:
		//	break;
		//}
		//debugOBJ_->wtf.scale.y = 0.1f;
		//debugOBJ_->SetColor({ 0,1,1,1 });
		debugOBJ_->Update();
	}

	if (registNum == 0) {
		ray->SetStart(pos);
		ray->SetDir(ret);
		if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
			return false;
		}
	}
	else if (registNum == 1) {
		ray->SetStart(points[0]);
		ray->SetDir(ret);
		if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
			return false;
		}
	}
	else if (registNum == 2) {
		ray->SetStart(points[1]);
		ray->SetDir(ret);
		if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
			return false;
		}
	}
	else if (registNum == 3) {
		ray->SetStart(points[2]);
		ray->SetDir(ret);
		if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
			return false;
		}
	}
	else if (registNum == 4) {
		ray->SetStart(points[3]);
		ray->SetDir(ret);
		if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
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
	if (registNum == POINT_1) {
		points[POINT_1] = point;
		pointActive_[POINT_1] = true;
		object_[POINT_1]->wtf.position = point;
		registNum = POINT_2;
	}
	else if (registNum == POINT_2) {
		points[POINT_2] = point;
		pointActive_[POINT_2] = true;
		object_[POINT_2]->wtf.position = point;
		registNum = POINT_3;
	}
	else if (registNum == POINT_3) {
		points[POINT_3] = point;
		pointActive_[POINT_3] = true;
		object_[POINT_3]->wtf.position = point;
		registNum = POINT_4;
	}
	else if (registNum == POINT_4) {
		points[POINT_4] = point;
		pointActive_[POINT_4] = true;
		object_[POINT_4]->wtf.position = point;
		registNum = POINT_5;
	}
	else if (registNum == POINT_5) {
		points[POINT_5] = point;
		pointActive_[POINT_5] = true;
		object_[POINT_5]->wtf.position = point;
		registNum = POINT_MAX;
		pointsMax = true;
	}
	else {

	}
	onPat_ = true;
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
		debuglengs[i] = moveVec[i].length();
	}
	for (uint32_t i = 0; i <= registNum; i++) {
		moveVec[i].nomalize();

	}
	isActive = true;
	nowPointNum = 0;
}
void PointDash::GoToPoint() {
	timeEnd = false;
	Vector3 inversVec3;
	if (isActive) {
		time++;

		easetime = (float)time / easeMaxTime;
		if (nowPointNum == 0 && time <= easeMaxTime && registNum >= 1) {
			resultVec = Easing::OutQuintVec3(startPos, points[0], (float)easetime);
			F_lengs = Easing::OutQuintFloat(30.0f, 10.0f, (float)easetime);
			inversVec3 = startPos - points[0];
			if (time == easeMaxTime - 1) {
				nowPointNum = 1;
				time = 1;
				easetime = 0;
				pointActive_[0] = false;
				timeEnd = true;
				onPat_ = true;
				inversVec3 = -inversVec3;
			}
		}
		if (nowPointNum == 1 && time <= easeMaxTime && registNum >= 2) {
			resultVec = Easing::OutQuintVec3(points[0], points[1], (float)easetime);
			inversVec3 = points[0] - points[1];
			if (time == easeMaxTime - 1) {
				resultVec = points[1];
				nowPointNum = 2;
				time = 1;
				easetime = 0;
				pointActive_[1] = false;
				timeEnd = true;
				onPat_ = true;
				inversVec3 = -inversVec3;
			}
		}
		if (nowPointNum == 2 && time <= easeMaxTime && registNum >= 3) {
			resultVec = Easing::OutQuintVec3(points[1], points[2], (float)easetime);
			inversVec3 = points[1] - points[2];
			if (time == easeMaxTime - 1) {
				resultVec = points[2];
				nowPointNum = 3;
				time = 1;
				easetime = 0;
				pointActive_[2] = false;
				timeEnd = true;
				onPat_ = true;
				inversVec3 = -inversVec3;
			}
		}
		if (nowPointNum == 3 && time <= easeMaxTime && registNum >= 4) {
			resultVec = Easing::OutQuintVec3(points[2], points[3], (float)easetime);
			inversVec3 = points[2] - points[3];
			if (time == easeMaxTime - 1) {
				resultVec = points[3];
				nowPointNum = 4;
				time = 1;
				easetime = 0;
				pointActive_[3] = false;
				timeEnd = true;
				onPat_ = true;
				inversVec3 = -inversVec3;
			}
		}
		if (nowPointNum == 4 && time <= 60 && registNum == 5) {
			resultVec = Easing::OutQuintVec3(points[3], points[4], (float)easetime);
			inversVec3 = points[3] - points[4];
			if (time >= easeMaxTime - 1) {
				resultVec = points[4];
				nowPointNum = 5;
				time = 1;
				easetime = 0;
				pointActive_[4] = false;
				timeEnd = true;
				inversVec3 = -inversVec3;
			}
		}
		// パーティクルなぜかXそのままYZ入れ替えると治る
		Vector3 patPos = { resultVec.x,resultVec.z,resultVec.y };
		if (onPat_) {
			//particle_->RandParticle(25, patPos, inversVec3);
		}
		onPat_ = false;
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
	pointsMax = false;
}

void PointDash::DebugImGui()
{
	int maxtime = (int)easeMaxTime;
	ImGui::Begin("PointDash");
	ImGui::Text("VectorSize:%d", points.size());
	ImGui::InputFloat3("Vec", &resultVec.x);
	ImGui::InputFloat("speeed :%f", &easeSpeed);
	ImGui::InputInt("Maxtime :%d", &maxtime);
	ImGui::Text("lengs1:%f", debuglengs[0]);
	ImGui::Text("lengs2:%f", debuglengs[1]);
	ImGui::Text("lengs3:%f", debuglengs[2]);
	ImGui::Text("lengs4:%f", debuglengs[3]);
	ImGui::Text("lengs5:%f", debuglengs[4]);
	ImGui::End();
	easeMaxTime = (uint32_t)maxtime;
}
