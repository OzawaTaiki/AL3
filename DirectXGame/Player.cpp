#include "Player.h"
#include "Input.h"
#include "MatrixFunction.h"
#include "VectorFunction.h"
#include <cassert>

Player::Player() {}

void Player::Initialize(Model* _model) {
	// NULLチェック
	assert(_model);
	model_ = _model;
	// ワールドトランス初期化
	worldTransform_.Initialize();
}

void Player::Update() {

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		Vector3 move = {(float)joyState.Gamepad.sThumbLX, 0.0f, (float)joyState.Gamepad.sThumbLY};
		if (joyState.Gamepad.sThumbLX != 0 || joyState.Gamepad.sThumbLY != 0) {

			const float speed = 0.3f;
			Vector3 normalizeMove = Normalize(move);
			move = normalizeMove * speed;

			Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);
			move = TransformNormal(move, rotateMatrix);

			worldTransform_.translation_ += move;

			normalizeMove = TransformNormal(normalizeMove, rotateMatrix);

			worldTransform_.rotation_.y = std::atan2(normalizeMove.x, normalizeMove.z);
		}
	}
	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& _viewProjection) { model_->Draw(worldTransform_, _viewProjection); }
