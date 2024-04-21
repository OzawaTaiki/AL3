#include "Enemy.h"
#include "VectorFunction.h"
#include <cassert>
#include "ImGuiManager.h"

void Enemy::Initialize(Model* _model, uint32_t _textrueHandle) {
	// NULLチェック
	assert(_model);
	model = _model;
	textureHandle = _textrueHandle;
	// ワールドトランス初期化
	worldTransform.Initialize();
}

void Enemy::Update() {
	Vector3 velocity(0, 0, -0.1f);
	worldTransform.translation_ += velocity;
	worldTransform.UpdateMatrix();

	Imgui();
}

void Enemy::Draw(ViewProjection& _viewProjection) { model->Draw(worldTransform, _viewProjection, textureHandle); }

void Enemy::SetTranslete(const Vector3& _translation) { worldTransform.translation_ = _translation; }

void Enemy::Imgui() {
	ImGui::Begin("Enemy");
	ImGui::DragFloat3("Translation", &worldTransform.translation_.x, 0.1f);
	ImGui::End();
}
