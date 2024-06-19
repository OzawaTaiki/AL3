#pragma once

#include "Model.h"
#include "Player.h"
#include "VectorFunction.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class EnemyBullet {
public:
	void initialize(Model* _model, const Vector3& _position, const Vector3& _velocity, uint32_t _textrueHandle = 0);
	void Update();
	void Draw(ViewProjection& _viewProjection);
	Vector3 GetWorldPosition();

	void OnCollision();


	bool IsDead() const { return isDead; };
	void SetPlayer(Player* _player) { player = _player; };

	static const int32_t kLifeTime = 60 * 5;

private:
	Model* model = nullptr;
	WorldTransform worldTransform;
	uint32_t textureHandle = 0;

	Player* player = nullptr;
	Vector3 velocity;

	int32_t deathTimer = kLifeTime;
	bool isDead = false;
};