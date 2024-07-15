#include "FollowCamera.h"
#include "MatrixFunction.h"
#include "VectorFunction.h"
#include "Input.h"

FollowCamera::FollowCamera() {}

FollowCamera::~FollowCamera() {}

void FollowCamera::Initialize() { viewProjection_.Initialize(); }

void FollowCamera::Update() {
	
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		float rotateSpeed = 0.00001f;
		viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX * rotateSpeed;
	}
	if (target_) {
		Vector3 offset = {0.0f, 5.0f, -20.0f};
		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_.rotation_);
		offset = TransformNormal(offset, rotateMatrix);
		viewProjection_.translation_ = target_->translation_ + offset;
	}

	

	viewProjection_.UpdateMatrix();
}
