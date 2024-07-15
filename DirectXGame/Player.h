#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player {
public:
	Player();

	void Initialize(Model* _model);
	void Update();
	void Draw(ViewProjection& _viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	void SetViewProjection(const ViewProjection* _viewProjection) { viewProjection_ = _viewProjection; };

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

	const ViewProjection* viewProjection_;
};