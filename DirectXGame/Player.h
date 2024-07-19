#pragma once
#include "BaseCharacter.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <numbers>
#include <vector>

enum Parts { Body, Head, RArm, LArm, Base };

class Player {
public:
	Player();

	void Initialize(const std::vector<Model*>& _models);
	void Update();
	void Draw(const ViewProjection& _viewProjection);

	const WorldTransform& GetWorldTransform() { return *worldTransform_[Base].get(); };
	void SetViewProjection(const ViewProjection* _viewProjection) { viewProjection_ = _viewProjection; };

	void ImGui();

private:
	void InitializeFloatingGimmick();
	void UpdateFloatingGimmick();

	std::vector<std::unique_ptr<WorldTransform>> worldTransform_;
	std::vector<Model*> models_;

	const ViewProjection* viewProjection_;

	float targetAngle_;
	// 浮遊アニメーション
	float floatingParameter_ = 0.0f;
	uint16_t floatingCycleFrameCount_ = 90;
	float stepPerFrame_ = 2.0f * std::numbers::pi_v<float> / floatingCycleFrameCount_;
	float floatAmplitude = 0.15f;
};