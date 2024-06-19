#pragma once

#include "Collider.h"
#include "EnemyBullet.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player;

class Enemy : public Collider {

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
	void SetPlayer(Player* _player) { player = _player; };

	const std::list<EnemyBullet*>& GetBullets() const { return bullets; };

	void InitializeApproachPhase();
	void UpdateApproachPhase();

	Vector3 GetWorldPosition() override;
	void OnCollision() override;

	static const int kFireInterval = 60;

private:
#ifdef _DEBUG
	void Imgui();
#endif // _DEBUG

	void LeavePhase();
	void ApproachPhase();

	void Fire();

	void (Enemy::*phase)();
	static void (Enemy::*phaseTable[])();

	WorldTransform worldTransform;
	Model* model = nullptr;
	uint32_t textureHandle = 0;

	std::list<EnemyBullet*> bullets;
	int32_t fireTimer = 0;

	Player* player = nullptr;

	const float radius = 2.0f;
};
