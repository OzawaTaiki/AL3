#pragma once
#include "Model.h"
#include "VectorFunction.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class PlayerBullet {
public:
	void initialize(Model* _model, const Vector3& _position, uint32_t _textrueHandle = 0);

	void Update();

	void Draw(const ViewProjection& _viewProjection);

private:
	Model* model = nullptr;
	WorldTransform worldTransform;
	uint32_t textureHandle = 0;
};