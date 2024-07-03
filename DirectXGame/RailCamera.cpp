#include "RailCamera.h"
#include "ImGuiManager.h"
#include "MatrixFunction.h"
#include "MyLib.h"
#include "PrimitiveDrawer.h"
#include "VectorFunction.h"
#include <algorithm>

void RailCamera::Initialize(const Vector3& _worldPos, const Vector3& _rotare) {

	worldTransform.Initialize();
	worldTransform.translation_ = _worldPos;
	worldTransform.rotation_ = _rotare;

	viewProjection.Initialize();

	controlPoints = {
	    {0,  0,  0 },
        {10, 10, 0 },
        {10, 15, 10},
        {20, 15, 13},
        {20, 0,  15},
        {30, 0,  20},
	};

	posT = 0;
	directionT = 0;
	speedT = deltaTime / 10.0f;
}

void RailCamera::Update() {

	pointsDrawing.clear();

	Imgui();
	CaluculateCatmulRompoint();

	Move();
	// worldTransform.translation_ += _move;
	// worldTransform.rotation_ += _rotare;
	worldTransform.UpdateMatrix();

	viewProjection.matView = MatrixFunction::Inverse(worldTransform.matWorld_);
}

void RailCamera::CamulRomDraw() {

	for (int i = 1; i < pointsDrawing.size() - 1; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(pointsDrawing[i - 1], pointsDrawing[i], {1.0f, 0.0f, 0.0f, 1.0f});
	}
	Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldTransform.translation_, worldTransform.translation_ + targetP, color);
}

Vector3 RailCamera::GetWorldPosition() {
	Vector3 result;
	result.x = worldTransform.matWorld_.m[3][0];
	result.y = worldTransform.matWorld_.m[3][1];
	result.z = worldTransform.matWorld_.m[3][2];
	return Vector3(result);
}

void RailCamera::CaluculateCatmulRompoint() {

	const size_t segmentCount = 100;

	for (size_t i = 0; i < segmentCount + 1; i++) {
		float t = 1.0f / segmentCount * i;
		Vector3 pos = CalculatePointCatmullRom(controlPoints, t);

		pointsDrawing.push_back(pos);
	}
}

void RailCamera::Move() {

	posT += speedT;
	posT = std::clamp(posT, 0.0f, 1.0f);
	directionT = posT + 0.005f;

	Vector3 position = CalculatePointCatmullRom(controlPoints, posT);
	worldTransform.translation_ = position;

	Vector3 target = CalculatePointCatmullRom(controlPoints, directionT);
	targetP = target;

	Vector3 foward = target - position;

	Vector3 normalizeDirection = VectorFunction::Normalize(foward);
	worldTransform.rotation_.y = std::atan2(normalizeDirection.x, normalizeDirection.z);
	float horizontalDistance = std::sqrt(normalizeDirection.x * normalizeDirection.x + normalizeDirection.z * normalizeDirection.z);

	worldTransform.rotation_.x = -std::atan2(normalizeDirection.y, horizontalDistance);
}

void RailCamera::Imgui() {
	ImGui::Begin("camera");
	ImGui::DragFloat3("translate", &worldTransform.translation_.x, 0.01f);
	ImGui::DragFloat3("rotate", &worldTransform.rotation_.x, 0.01f);
	ImGui::End();
}
