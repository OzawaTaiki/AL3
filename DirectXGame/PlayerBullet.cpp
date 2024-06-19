#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::initialize(Model* _model, const Vector3& _position, const Vector3& _velocity, uint32_t _textrueHandle) {
	// NULLチェック
	assert(_model);
	model = _model;
	textureHandle = _textrueHandle;
	// ワールドトランス初期化
	worldTransform.Initialize();

	worldTransform.translation_ = _position;
	velocity = _velocity;
}

void PlayerBullet::Update() {

	if (--deathTimer <= 0) {
		isDead = true;
	}
	worldTransform.translation_ += velocity;
	worldTransform.UpdateMatrix();
}

void PlayerBullet::Draw(const ViewProjection& _viewProjection) { model->Draw(worldTransform, _viewProjection, textureHandle); }

Vector3 PlayerBullet::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform.matWorld_.m[3][0];
	worldPos.y = worldTransform.matWorld_.m[3][1];
	worldPos.z = worldTransform.matWorld_.m[3][2];

	return worldPos;
}

void PlayerBullet::OnCollision() {}
