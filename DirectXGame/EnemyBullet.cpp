#include "EnemyBullet.h"
#include <cassert>

void EnemyBullet::initialize(Model* _model, const Vector3& _position, const Vector3& _velocity, uint32_t _textrueHandle) {
	// NULLチェック
	assert(_model);
	model = _model;
	textureHandle = _textrueHandle;
	// ワールドトランス初期化
	worldTransform.Initialize();

	worldTransform.translation_ = _position;
	velocity = _velocity;

	SetCollisionAttribute(0b10);
	SetCollisionMask(0b11111101);
}

void EnemyBullet::Update() {
	if (--deathTimer <= 0) {
		isDead = true;
	}
	worldTransform.translation_ += velocity;
	worldTransform.UpdateMatrix();
}

void EnemyBullet::Draw(ViewProjection& _viewProjection) { model->Draw(worldTransform, _viewProjection, textureHandle); }

void EnemyBullet::OnCollision() { isDead = true; }

Vector3 EnemyBullet::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform.translation_.x;
	worldPos.y = worldTransform.translation_.y;
	worldPos.z = worldTransform.translation_.z;

	return worldPos;
}
