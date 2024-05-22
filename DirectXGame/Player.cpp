#include "Player.h"
#include "ImGuiManager.h"
#include "MyLib.h"
#include <TextureManager.h>
#include <WinApp.h>
#include <cassert>

Player::~Player() {
	for (PlayerBullet* bullet : bullets) {
		delete bullet;
	}
	bullets.clear();
	delete sprite2DReticle;
}

void Player::Initialize(Model* _model, uint32_t _textrueHandle, uint32_t _reticleTextrueHandle, const Vector3& _pos) {
	// NULLチェック
	assert(_model);
	model = _model;
	worldTransform.translation_ = _pos;
	textureHandle = _textrueHandle;
	texture3DReticle = TextureManager::Load("cube/cube.jpg");

	sprite2DReticle = Sprite::Create(_reticleTextrueHandle, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});

	// ワールドトランス初期化
	worldTransform.Initialize();
	woldTransform3DReticle.Initialize();
	input = Input::GetInstance();
}

void Player::Update(ViewProjection& _viewProjection) {

#ifdef _DEBUG
	ImGui();
#endif // _DEBUG

	bullets.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	rotate();

	Vector3 move = {0, 0, 0}; // キャラクターの移動ベクトル

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
	move = VectorFunction::Normalize(move)*kCharacterSpeed;

	Attack();
	for (PlayerBullet* bullet : bullets) {
		bullet->Update();
	}

	// 座標移動
	worldTransform.translation_ += move;

	Vector3 minLine = {-34.0f, -18.0f, -45.0f};
	Vector3 maxLine = {34.0f, 18.0f, 45.0f};

	VectorFunction::Clamp(worldTransform.translation_, minLine, maxLine);

	// 行列更新
	worldTransform.UpdateMatrix();
	// worldTransform.matWorld_ = MatrixFunction::MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
	// worldTransform.TransferMatrix();

	Update3DReticle();
	Update2DReticle(_viewProjection);
}

void Player::Draw(ViewProjection& _viewProjection) {
	model->Draw(worldTransform, _viewProjection, textureHandle);
	for (PlayerBullet* bullet : bullets) {
		bullet->Draw(_viewProjection);
	}

	//model->Draw(woldTransform3DReticle, _viewProjection, texture3DReticle);
}

void Player::DrawUI() { sprite2DReticle->Draw(); }

Vector3 Player::GetWorldPositoin() {
	Vector3 worldPos;

	worldPos.x = worldTransform.matWorld_.m[3][0];
	worldPos.y = worldTransform.matWorld_.m[3][1];
	worldPos.z = worldTransform.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Player::Get3DReticleWorldPositoin() {
	Vector3 worldPos;

	worldPos.x = woldTransform3DReticle.matWorld_.m[3][0];
	worldPos.y = woldTransform3DReticle.matWorld_.m[3][1];
	worldPos.z = woldTransform3DReticle.matWorld_.m[3][2];

	return worldPos;
}

void Player::OnCollision() {}

void Player::rotate() {
	if (input->PushKey(DIK_A)) {
		worldTransform.rotation_.y -= 0.02f;
	} else if (input->PushKey(DIK_D)) {
		worldTransform.rotation_.y += 0.02f;
	}
}

void Player::Attack() {
	// if (input->TriggerKey(DIK_SPACE)) {
	if (input->PushKey(DIK_SPACE)) {

		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = Get3DReticleWorldPositoin() - GetWorldPositoin();
		velocity = VectorFunction::Normalize(velocity) * kBulletSpeed;
		// velocity = VectorFunction::TransformNormal(velocity, worldTransform.matWorld_);

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->initialize(model, GetWorldPositoin(), velocity);

		bullets.push_back(newBullet);
	}
}

void Player::Update3DReticle() {
	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = {0.0f, 0.0f, 1.0f};
	offset = VectorFunction::TransformNormal(offset, worldTransform.matWorld_);
	offset = VectorFunction::Normalize(offset) * kDistancePlayerTo3DReticle;
	woldTransform3DReticle.translation_ = GetWorldPositoin() + offset;
	woldTransform3DReticle.UpdateMatrix();
}

void Player::Update2DReticle(ViewProjection& _viewProjection) {

	Vector3 positionReticle = Get3DReticleWorldPositoin();

	// ビューポート行列
	Matrix4x4 matViewport = MatrixFunction::MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	// ビュー行列とプロジェクション行列、ビューポート行列を合成する
	Matrix4x4 matViewProjectionViewport = _viewProjection.matView * _viewProjection.matProjection * matViewport;

	// ワールド→スクリーン座標変換(ここで3Dから2Dになる)
	positionReticle = VectorFunction::Transform(positionReticle, matViewProjectionViewport);

	// スプライトのレティクルに座標設定
	sprite2DReticle->SetPosition(Vector2(positionReticle.x, positionReticle.y));
}

void Player::ImGui() {
	ImGui::Begin("Player");
	ImGui::DragFloat3("Scale", &worldTransform.scale_.x, 0.1f);
	ImGui::DragFloat3("Rotation", &worldTransform.rotation_.x, 0.1f);
	ImGui::DragFloat3("Translation", &worldTransform.translation_.x, 0.1f);
	ImGui::End();
}
