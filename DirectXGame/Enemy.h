#pragma once

#include "EnemyBullet.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>
#include "TimedCall.h"

class Enemy {

	enum class Phase {
		Approach, // 接近する
		Leave     // 離脱する
	};

public:
	~Enemy();

	void Initialize(Model* _model, uint32_t _textrueHandle);
	void Update();
	void Draw(ViewProjection& _viewProjection);

	void SetTranslete(const Vector3& _translation);

	void InitializeApproachPhase();
	void UpdateApproachPhase();

	void ShootAndResetTimer();

	static const int kFireInterval = 60;

private:
	void LeavePhase();
	void ApproachPhase();

	void Fire();

	std::list<TimedCall*> timedCall;

	    void (Enemy::*phase)();
	static void (Enemy::*phaseTable[])();

	WorldTransform worldTransform;
	Model* model = nullptr;
	uint32_t textureHandle = 0;

	std::list<EnemyBullet*> bullets;
	int32_t fireTimer = 0;

#ifdef _DEBUG
	void Imgui();
#endif // _DEBUG
};
