#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::initialize(Model* _model, const Vector3& _position, uint32_t _textrueHandle) {
	// NULLチェック
	assert(_model);
	model = _model;
	textureHandle = _textrueHandle;
	// ワールドトランス初期化
	worldTransform.Initialize();

	worldTransform.translation_ = _position;
}

void PlayerBullet::Update() { worldTransform.UpdateMatrix(); }

void PlayerBullet::Draw(const ViewProjection& _viewProjection) { model->Draw(worldTransform, _viewProjection, textureHandle); }