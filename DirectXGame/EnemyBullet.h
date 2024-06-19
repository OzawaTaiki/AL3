#pragma once

#include "Collider.h"
#include "Model.h"
#include "VectorFunction.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class EnemyBullet : public Collider {
public:
	void initialize(Model* _model, const Vector3& _position, const Vector3& _velocity, uint32_t _textrueHandle = 0);
	void Update();
	void Draw(ViewProjection& _viewProjection);

	bool IsDead() const { return isDead; };
	Vector3 GetWorldPosition() override;
	void OnCollision() override;

	static const int32_t kLifeTime = 60 * 5;

private:
	Model* model = nullptr;
	WorldTransform worldTransform;
	uint32_t textureHandle = 0;

	Vector3 velocity;
	int32_t deathTimer = kLifeTime;
	bool isDead = false;

	const float radius = 2.0f;
};