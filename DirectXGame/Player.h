#pragma once
#include "BaseCharacter.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <vector>

enum Parts {
	Body,
	Head,
	RArm,
	LArm
};

class Player {
public:
	Player();

	void Initialize(const std::vector<Model*>& _models);
	void Update();
	void Draw(const ViewProjection& _viewProjection);

	// const WorldTransform& GetWorldTransform() { return worldTransform_; };
	void SetViewProjection(const ViewProjection* _viewProjection) { viewProjection_ = _viewProjection; };

private:
	std::vector<WorldTransform> worldTransform_;
	std::vector<Model*> models_;

	const ViewProjection* viewProjection_;

	float targetAngle_;
};