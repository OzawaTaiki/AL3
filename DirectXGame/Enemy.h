#pragma once

#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Enemy {

public:
	void Initialize(Model* _model, uint32_t _textrueHandle);
	void Update();
	void Draw(ViewProjection& _viewProjection);

	void SetTranslete(const Vector3& _translation);

private:
	void Imgui();

	WorldTransform worldTransform;
	Model* model = nullptr;
	uint32_t textureHandle = 0;

};
