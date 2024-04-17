#include "Player.h"
#include "ImGuiManager.h"
#include "MyLib.h"
#include <cassert>

void PLayer::Initialize(Model* _model, uint32_t _textrueHandle) {
	// NULLチェック
	assert(_model);
	model = _model;
	textureHandle = _textrueHandle;
	// ワールドトランス初期化
	worldTransform.Initialize();

	input = Input::GetInstance();
}

void PLayer::Update() {

#ifdef _DEBUG
	ImGui();
#endif // _DEBUG

	Vector3 move = {0, 0, 0};           // キャラクターの移動ベクトル
	const float kCharacterSpeed = 0.2f; // キャラクターの速さ

	// 移動ベクトルの変更
	if (input->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	if (input->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	move = VectorFunction::Normalize(move);

	
	// 座標移動
	worldTransform.translation_ += move;
	
	Vector3 minLine = {-34.0f, -18.0f,-45.0f};
	Vector3 maxLine = {34.0f, 18.0f,45.0f};
	
	VectorFunction::Clamp(worldTransform.translation_, minLine, maxLine);

	// 行列更新
	worldTransform.matWorld_ = MatrixFunction::MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
	worldTransform.TransferMatrix();
}

void PLayer::Draw(ViewProjection& _viewProjection) { model->Draw(worldTransform, _viewProjection, textureHandle); }

void PLayer::ImGui() {
	ImGui::Begin("Player");
	ImGui::DragFloat3("Scale", &worldTransform.scale_.x, 0.1f);
	ImGui::DragFloat3("Rotation", &worldTransform.rotation_.x, 0.1f);
	ImGui::DragFloat3("Translation", &worldTransform.translation_.x, 0.1f);
	ImGui::End();
}
