#include "EnemyBullet.h"
#include "MatrixFunction.h"
#include <cassert>

void EnemyBullet::initialize(Model* _model, const Vector3& _position, const Vector3& _velocity, uint32_t _textrueHandle) {
	// NULLチェック
	assert(_model);
	model = _model;
	textureHandle = _textrueHandle;
	// ワールドトランス初期化

	worldTransform.Initialize();

	worldTransform.translation_ = _position;
	worldTransform.scale_.x = 0.5f;
	worldTransform.scale_.y = 0.5f;
	worldTransform.scale_.z = 3.0f;
	velocity = _velocity;

	Vector3 normalizeVelocity = VectorFunction::Normalize(velocity);
	worldTransform.rotation_.y = std::atan2(normalizeVelocity.x, normalizeVelocity.z);
	float horizontalDistance = std::sqrt(normalizeVelocity.x * normalizeVelocity.x + normalizeVelocity.z * normalizeVelocity.z);

	worldTransform.rotation_.x = -std::atan2(normalizeVelocity.y, horizontalDistance);
}

void EnemyBullet::Update() {
	if (--deathTimer <= 0) {
		isDead = true;
	}
	worldTransform.translation_ += velocity;

	// TODO: p1~ 何も手つけてない
	const float kBulletSpeed = 1.0f;

	Vector3 toPlayer = player->GetWorldPositoin() - GetWorldPos();

	Vector3 normalizeToPlayer = VectorFunction::Normalize(toPlayer);
	Vector3 normalizeVelocity = VectorFunction::Normalize(velocity);

	velocity = VectorFunction::Slerp(normalizeVelocity, normalizeToPlayer, 0.005f) * kBulletSpeed;

	worldTransform.rotation_.y = std::atan2(normalizeVelocity.x, normalizeVelocity.z);
	float horizontalDistance = std::sqrt(normalizeVelocity.x * normalizeVelocity.x + normalizeVelocity.z * normalizeVelocity.z);

	worldTransform.rotation_.x = -std::atan2(normalizeVelocity.y, horizontalDistance);

	worldTransform.UpdateMatrix();
}

void EnemyBullet::Draw(ViewProjection& _viewProjection) { model->Draw(worldTransform, _viewProjection, textureHandle); }

Vector3 EnemyBullet::GetWorldPos() {
	Vector3 worldPos;
	worldPos.x = worldTransform.matWorld_.m[3][0];
	worldPos.y = worldTransform.matWorld_.m[3][1];
	worldPos.z = worldTransform.matWorld_.m[3][2];

	return worldPos;
}
