#include "skydoom.h"
#include "ImGuiManager.h"
#include "MatrixFunction.h"
#include <cassert>

Skydoom::~Skydoom() {}

void Skydoom::Initialze(Model* _model) {
	assert(_model);
	model = _model;
	worldTransform.Initialize();
	worldTransform.scale_ = {500.0f, 500.0f, 500.0f};
}

void Skydoom::Update() {
	ImGui();
	worldTransform.matWorld_ = MatrixFunction::MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
	worldTransform.TransferMatrix();
}

void Skydoom::Draw(ViewProjection& _viewProjection) { model->Draw(worldTransform, _viewProjection); }

void Skydoom::ImGui() {
	ImGui::Begin("skydoom");
	ImGui::DragFloat3("Scale", &worldTransform.scale_.x, 0.1f);
	ImGui::DragFloat3("Rotation", &worldTransform.rotation_.x, 0.1f);
	ImGui::DragFloat3("Translation", &worldTransform.translation_.x, 0.1f);
	ImGui::End();
}
