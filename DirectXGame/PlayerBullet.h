#pragma once
#include "Model.h"
#include "VectorFunction.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class PlayerBullet {
public:
	void initialize(Model* _model, const Vector3& _position, const Vector3& _velocity, uint32_t _textrueHandle = 0);

	void Update();

	void Draw(const ViewProjection& _viewProjection);

	bool IsDead() const { return isDead; };

	static const uint32_t kLifeTime = 60 * 5;

private:
	Model* model = nullptr;
	WorldTransform worldTransform;
	uint32_t textureHandle = 0;

	Vector3 velocity;
	int32_t deathTimer = kLifeTime;
	bool isDead = false;
};