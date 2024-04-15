#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"ViewProjection.h"

class PLayer {
public:
	void Initialize(Model* _model, uint32_t _textrueHandle);
	void Update();
	void Draw(ViewProjection& _viewProjection);

private:
	WorldTransform worldTransform;
	Model* model = nullptr;
	uint32_t textureHandle = 0;
};