#pragma once

#include "EnemyBullet.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player;
class GameScene;

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
	void SetPlayer(Player* _player) { player = _player; };

	Vector3 GetWorldPositoin();

	void InitializeApproachPhase();
	void UpdateApproachPhase();

	void OnCollision();

	void SetGameScene(GameScene* _gameScene) { gameScene = _gameScene; }

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

	int32_t fireTimer = 0;

	Player* player = nullptr;
	GameScene* gameScene = nullptr;

	const float radius = 2.0f;
};
