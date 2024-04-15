#include "Player.h"
#include <cassert>

void PLayer::Initialize(Model* _model, uint32_t _textrueHandle) {
	//NULLチェック
	assert(_model);
	model = _model;
	textureHandle = _textrueHandle;
	//ワールドトランス初期化
	worldTransform.Initialize();
}

void PLayer::Update() { worldTransform.TransferMatrix(); }

void PLayer::Draw(ViewProjection& _viewProjection) { model->Draw(worldTransform, _viewProjection, textureHandle); }
