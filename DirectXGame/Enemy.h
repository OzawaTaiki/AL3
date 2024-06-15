#pragma once

#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "BaseEnemyState.h"

class Enemy {

	enum class Phase {
		Approach, // 接近する
		Leave     // 離脱する
	};

public:
	void Initialize(Model* _model, uint32_t _textrueHandle);
	void Update();
	void Draw(ViewProjection& _viewProjection);

	void AddVelocity(const Vector3& _velocity);

	void SetTranslate(const Vector3& _translate);
	void ChangeState(std::unique_ptr<BaseEnemyState> _state);

	Vector3 GetWorldPos();

private:
#ifdef _DEBUG
	void Imgui();
#endif // _DEBUG

	//void LeavePhase();
	//void ApproachPhase();


	//void (Enemy::*phase)();
	//static void (Enemy::*phaseTable[])();

	std ::unique_ptr<BaseEnemyState> state;

	WorldTransform worldTransform;
	Model* model = nullptr;
	uint32_t textureHandle = 0;
};
