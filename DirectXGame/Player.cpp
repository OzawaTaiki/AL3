#include "Player.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "MatrixFunction.h"
#include "MyLib.h"
#include "VectorFunction.h"
#include <cassert>

Player::Player() {}

void Player::Initialize(Model* _model) {
	// NULLチェック
	assert(_model);
	model_ = _model;
	// ワールドトランス初期化

	targetAngle_ = 0.0f;

	worldTransform_.Initialize();
}

void Player::Update() {

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		// 閾値
		const float threshold = 0.7f;
		bool isMoving = false;

		Vector3 move = {(float)joyState.Gamepad.sThumbLX, 0.0f, (float)joyState.Gamepad.sThumbLY};
		if (Length(move) > threshold) {
			isMoving = true;
		}

		if (isMoving) {
			const float speed = 0.3f;
			Vector3 normalizeMove = Normalize(move);
			move = normalizeMove * speed;

			Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);
			move = TransformNormal(move, rotateMatrix);

			worldTransform_.translation_ += move;

			normalizeMove = TransformNormal(normalizeMove, rotateMatrix);
			targetAngle_ = std::atan2(normalizeMove.x, normalizeMove.z);
			// worldTransform_.rotation_.y = std::atan2(normalizeMove.x, normalizeMove.z);
		}
	}

	ImGui::Begin("window");
	ImGui::DragFloat3("rotate", &worldTransform_.rotation_.x, 0.01f);
	ImGui::Text("%.3f", targetAngle_);
	ImGui::End();
	worldTransform_.rotation_.y = LerpShortAngle(worldTransform_.rotation_.y, targetAngle_, 0.1f);

	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& _viewProjection) { model_->Draw(worldTransform_, _viewProjection); }
