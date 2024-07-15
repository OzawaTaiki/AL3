#include "Ground.h"
#include "MatrixFunction.h"
#include <cassert>

Ground::Ground() {}

Ground::~Ground() {}

void Ground::Initialize(Model* _model) {
	assert(_model);
	model_ = _model;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {50.0f, 1.0f, 50.0f};
}

void Ground::Update() {
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Ground::Draw(const ViewProjection& _viewProjection) { model_->Draw(worldTransform_, _viewProjection); }
