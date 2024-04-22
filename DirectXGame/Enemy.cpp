#include "Enemy.h"
#include "ImGuiManager.h"
#include "VectorFunction.h"
#include <cassert>

void Enemy::Initialize(Model* _model, uint32_t _textrueHandle) {
	// NULLチェック
	assert(_model);
	model = _model;
	textureHandle = _textrueHandle;
	// ワールドトランス初期化
	worldTransform.Initialize();
}

void Enemy::Update() {

	switch (phase) {
	case Phase::Approach:
	default:
		ApproachPhase();
		break;
	case Phase::Leave:
		LeavePhase();
		break;
	}

	worldTransform.UpdateMatrix();

	Imgui();
}

void Enemy::Draw(ViewProjection& _viewProjection) { model->Draw(worldTransform, _viewProjection, textureHandle); }

void Enemy::SetTranslete(const Vector3& _translation) { worldTransform.translation_ = _translation; }

void Enemy::Imgui() {
	ImGui::Begin("Enemy");
	ImGui::DragFloat3("Translation", &worldTransform.translation_.x, 0.1f);
	ImGui::Text("%s", phase == Phase::Approach ? "Approach" : "Leave");
	ImGui::End();
}

void Enemy::LeavePhase() {
	Vector3 velocity = {0, 0, -0.3f};
	worldTransform.translation_ -= velocity;
}
void Enemy::ApproachPhase() {

	Vector3 velocity(0, 0, -0.1f);
	worldTransform.translation_ += velocity;
	if (worldTransform.translation_.z < 0.0f)
		phase = Phase::Leave;
}
