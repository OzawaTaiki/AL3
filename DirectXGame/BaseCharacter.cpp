#include "BaseCharacter.h"

void BaseCharacter::Initialize(const std::vector<Model*>& _models) {
	models_ = _models;
	worldTransform_.Initialize();
}

void BaseCharacter::Update() { worldTransform_.UpdateMatrix(); }


void BaseCharacter::Draw(const ViewProjection& _viewProjection) {
	for (Model* model : models_) {
		model->Draw(worldTransform_, _viewProjection);
	}
}
