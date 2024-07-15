#include "Player.h"
#include <cassert>

void Player::Initialize(Model* _model) {
	//NULLチェック
	assert(_model);
	model = _model;
	//ワールドトランス初期化
	worldTransform.Initialize();
}

void Player::Update() { worldTransform.TransferMatrix(); }

void Player::Draw(ViewProjection& _viewProjection) { model->Draw(worldTransform, _viewProjection); }
