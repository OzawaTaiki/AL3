#include "Enemy.h"
#include "EnemyStateApproach.h"
#include "ImGuiManager.h"
#include "VectorFunction.h"
#include <cassert>

//void (Enemy::*Enemy::phaseTable[])() = {&Enemy::ApproachPhase, &Enemy::LeavePhase};

void Enemy::Initialize(Model* _model, uint32_t _textrueHandle) {
	// NULLチェック
	assert(_model);
	model = _model;
	textureHandle = _textrueHandle;
	// ワールドトランス初期化
	worldTransform.Initialize();
	ChangeState(std::make_unique<EnemyStateApproach>(this));
	//phase = phaseTable[(int)Phase::Approach];
}

void Enemy::Update() {

	//(this->*Enemy::phase)();
	state->Update();
	worldTransform.UpdateMatrix();

	Imgui();
}

void Enemy::Draw(ViewProjection& _viewProjection) { model->Draw(worldTransform, _viewProjection, textureHandle); }

void Enemy::AddVelocity(const Vector3& _velocity) { worldTransform.translation_ += _velocity; }

void Enemy::SetTranslate(const Vector3& _translate) { worldTransform.translation_ = _translate; }

void Enemy::ChangeState(std::unique_ptr<BaseEnemyState> _state) { state = std::move(_state); }

Vector3 Enemy::GetWorldPos() {
	Vector3 result;
	result.x = worldTransform.matWorld_.m[3][0];
	result.y = worldTransform.matWorld_.m[3][1];
	result.z = worldTransform.matWorld_.m[3][2];
	return Vector3(result);
}

void Enemy::Imgui() {
	ImGui::Begin("Enemy");
	ImGui::DragFloat3("Translation", &worldTransform.translation_.x, 0.1f);
	ImGui::Text("%s", state->DebugLog().c_str());
	ImGui::End();
}
//
//void Enemy::LeavePhase() {
//	Vector3 velocity = {0, 0, -0.3f};
//	worldTransform.translation_ -= velocity;
//}
//void Enemy::ApproachPhase() {
//
//	Vector3 velocity(0, 0, -0.1f);
//	worldTransform.translation_ += velocity;
//	if (worldTransform.translation_.z < 0.0f) {
//		phase = phaseTable[(int)Phase::Leave];
//	}
//}
