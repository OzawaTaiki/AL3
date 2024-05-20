#include "RailCamera.h"
#include "ImGuiManager.h"
#include "MatrixFunction.h"
#include "VectorFunction.h"

void RailCamera::Initialize(const Vector3& _worldPos, const Vector3& _rotare) {

	worldTransform.Initialize();
	worldTransform.translation_ = _worldPos;
	worldTransform.rotation_ = _rotare;

	viewProjection.Initialize();
}

void RailCamera::Update(const Vector3& _move, const Vector3& _rotare) {

	Imgui();
	worldTransform.translation_ += _move;
	worldTransform.rotation_ += _rotare;
	worldTransform.UpdateMatrix();
	//worldTransform.matWorld_ = MatrixFunction::MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
	//worldTransform.TransferMatrix();

	viewProjection.matView = MatrixFunction::Inverse(worldTransform.matWorld_);
}

void RailCamera::Imgui() {
	ImGui::Begin("camera");
	ImGui::DragFloat3("translate", &worldTransform.translation_.x, 0.01f);
	ImGui::DragFloat3("rotate", &worldTransform.rotation_.x, 0.01f);
	ImGui::End();
}
