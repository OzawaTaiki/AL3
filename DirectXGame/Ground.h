#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Ground {
public:
	Ground();
	~Ground();

	void Initialize(Model* _model);
	void Update();
	void Draw(const ViewProjection& _viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};
