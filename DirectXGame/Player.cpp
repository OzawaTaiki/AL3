#include "Player.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "MatrixFunction.h"
#include "MyLib.h"
#include "VectorFunction.h"
#include <cassert>

Player::Player() {}

void Player::Initialize(const std::vector<Model*>& _models) {
	// NULLチェック
	models_ = _models;
	// ワールドトランス初期化

	targetAngle_ = 0.0f;

	// パーツたち
	for (size_t index = 0; index < models_.size(); index++) {
		worldTransform_.push_back(std::make_unique<WorldTransform>());
		worldTransform_.back()->Initialize();
	}
	// base
	worldTransform_.push_back(std::make_unique<WorldTransform>());
	worldTransform_.back()->Initialize();

	worldTransform_[Body]->parent_ = worldTransform_[Base].get();
	worldTransform_[Head]->parent_ = worldTransform_[Body].get();
	worldTransform_[RArm]->parent_ = worldTransform_[Body].get();
	worldTransform_[LArm]->parent_ = worldTransform_[Body].get();

	worldTransform_[Body]->translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[Head]->translation_ = {0.0f, 3.6f, 0.0f};
	worldTransform_[RArm]->translation_ = {1.2f, 3.8f, 0.0f};
	worldTransform_[LArm]->translation_ = {-1.2f, 3.8f, 0.0f};

	InitializeFloatingGimmick();
}

void Player::Update() {

	ImGui();
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

			worldTransform_[Base]->translation_ += move;

			normalizeMove = TransformNormal(normalizeMove, rotateMatrix);
			targetAngle_ = std::atan2(normalizeMove.x, normalizeMove.z);
			// worldTransform_.rotation_.y = std::atan2(normalizeMove.x, normalizeMove.z);
		}
	}

	worldTransform_[Base]->rotation_.y = LerpShortAngle(worldTransform_[Base]->rotation_.y, targetAngle_, 0.1f);

	UpdateFloatingGimmick();

	worldTransform_[Base]->UpdateMatrix();
	for (size_t i = 0; i < worldTransform_.size(); i++) {
		worldTransform_[i]->UpdateMatrix();
	}
}

void Player::Draw(const ViewProjection& _viewProjection) {
	models_[Body]->Draw(*worldTransform_[Body], _viewProjection);
	models_[Head]->Draw(*worldTransform_[Head], _viewProjection);
	models_[RArm]->Draw(*worldTransform_[RArm], _viewProjection);
	models_[LArm]->Draw(*worldTransform_[LArm], _viewProjection);
}
void Player::ImGui() {
	// ImGui::SetNextWindowSize(ImVec2{300, 100});
	// ImGui::SetNextWindowPos(ImVec2{0, 0});
	ImGui::Begin("parts");
	ImGui::BeginTabBar("parts");
	std::string tabName[] = {"Body ", " Haed ", " RArm ", " LArm ", "Base"};
	for (size_t i = 0; i < worldTransform_.size(); i++) {
		if (ImGui::BeginTabItem(tabName[i].c_str())) {
			ImGui::DragFloat3("rotate", &worldTransform_[i]->rotation_.x, 0.01f);
			ImGui::DragFloat3("translate", &worldTransform_[i]->translation_.x, 0.1f);
			ImGui::EndTabItem();
		}
	}
	ImGui::EndTabBar();

	ImGui::Spacing();
	ImGui::Text("floatingAnimation");
	ImGui::Separator();
	int imStep = floatingCycleFrameCount_;
	ImGui::SliderInt("step", &imStep, 1, 256);
	floatingCycleFrameCount_ = static_cast<int16_t>(imStep);
	stepPerFrame_ = 2.0f * std::numbers::pi_v<float> / floatingCycleFrameCount_;
	ImGui::SliderFloat("amplitude", &floatAmplitude, 0.01f, 1.0f);

	ImGui::End();
}
void Player::InitializeFloatingGimmick() { floatingParameter_ = 0.0f; }
void Player::UpdateFloatingGimmick() {
	floatingParameter_ += stepPerFrame_;
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * std::numbers::pi_v<float>);
	worldTransform_[Body]->translation_.y = std::sin(floatingParameter_) * floatAmplitude;
};
