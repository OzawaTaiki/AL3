#pragma once

#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Enemy {

	enum class Phase {
		Approach, // 接近する
		Leave     // 離脱する
	};

public:
	void Initialize(Model* _model, uint32_t _textrueHandle);
	void Update();
	void Draw(ViewProjection& _viewProjection);

	void SetTranslete(const Vector3& _translation);

private:
#ifdef _DEBUG
	void Imgui();
#endif // _DEBUG

	void LeavePhase();
	void ApproachPhase();

	Phase phase = Phase::Approach;

	WorldTransform worldTransform;
	Model* model = nullptr;
	uint32_t textureHandle = 0;
};
