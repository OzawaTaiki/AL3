#include "RailCamera.h"
#include "ImGuiManager.h"
#include "MatrixFunction.h"
#include "MyLib.h"
#include "PrimitiveDrawer.h"
#include "VectorFunction.h"

void RailCamera::Initialize(const Vector3& _worldPos, const Vector3& _rotare) {

	worldTransform.Initialize();
	worldTransform.translation_ = _worldPos;
	worldTransform.rotation_ = _rotare;

	viewProjection.Initialize();

	controlPoints = {
	    {0,  0,  0},
        {10, 10, 0},
        {10, 15, 0},
        {20, 15, 0},
        {20, 0,  0},
        {30, 0,  0},
	};
}

void RailCamera::Update(const Vector3& _move, const Vector3& _rotare) {

	Imgui();
	worldTransform.translation_ += _move;
	worldTransform.rotation_ += _rotare;
	worldTransform.UpdateMatrix();
	// worldTransform.matWorld_ = MatrixFunction::MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
	// worldTransform.TransferMatrix();

	viewProjection.matView = MatrixFunction::Inverse(worldTransform.matWorld_);
}

void RailCamera::CamulRomDraw() {
	std::vector<Vector3> pointsDrawing;
	const size_t segmentCount = 100;

	for (size_t i = 0; i < segmentCount + 1; i++) {
		float t = 1.0f / segmentCount * i;
		Vector3 pos = CalculatePointCatmullRom(controlPoints, t);

		pointsDrawing.push_back(pos);
	}
	for (int i = 1; i < pointsDrawing.size() - 1; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(pointsDrawing[i - 1], pointsDrawing[i], {1.0f, 0.0f, 0.0f, 1.0f});
	}
}

void RailCamera::Imgui() {
	ImGui::Begin("camera");
	ImGui::DragFloat3("translate", &worldTransform.translation_.x, 0.01f);
	ImGui::DragFloat3("rotate", &worldTransform.rotation_.x, 0.01f);
	ImGui::End();
}
