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
	Move();

	Vector3 move = {0, 0, 0}; // キャラクターの移動ベクトル

	// Update3DReticle();
	ScreenToWorld(_viewProjection);
	// Update2DReticle(_viewProjection);

	Attack();
	for (PlayerBullet* bullet : bullets) {
		bullet->Update();
	}

	Vector3 minLine = {-34.0f, -18.0f, -45.0f};
	Vector3 maxLine = {34.0f, 18.0f, 45.0f};

	VectorFunction::Clamp(worldTransform.translation_, minLine, maxLine);

	// 行列更新
	worldTransform.UpdateMatrix();
	// worldTransform.matWorld_ = MatrixFunction::MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
	// worldTransform.TransferMatrix();
}

void Player::Draw(ViewProjection& _viewProjection) {
	model->Draw(worldTransform, _viewProjection, textureHandle);
	for (PlayerBullet* bullet : bullets) {
		bullet->Draw(_viewProjection);
	}

	// model->Draw(woldTransform3DReticle, _viewProjection, texture3DReticle);
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

void Player::Move() {
	Vector3 move = {0, 0, 0}; // キャラクターの移動ベクトル

	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;

	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	} else {
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
	}

	move = VectorFunction::Normalize(move) * kCharacterSpeed;

	// 座標移動
	worldTransform.translation_ += move;
}

void Player::Attack() {

	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;

	if (input->PushKey(DIK_SPACE) || (Input::GetInstance()->GetJoystickState(0, joyState) && (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER))) {

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

void Player::ScreenToWorld(ViewProjection& _viewProjection) {

	// スプライトの現在座標を取得
	Vector2 spritePosition = sprite2DReticle->GetPosition();

	XINPUT_STATE joyState;

	// ジョイスティック状態取得
	if (Input ::GetInstance()->GetJoystickState(0, joyState)) {
		spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 10.0f;
		spritePosition.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 10.0f;
		// スプライトの座標変更を反映
		sprite2DReticle->SetPosition(spritePosition);

	} else {

		POINT mousePosition;
		// マウス座標（スクリーン）を得る
		GetCursorPos(&mousePosition);
		// クライアントエリア座標に変換
		HWND hwnd = WinApp::GetInstance()->GetHwnd();
		ScreenToClient(hwnd, &mousePosition);

		sprite2DReticle->SetPosition(Vector2((float)mousePosition.x, (float)mousePosition.y));
	}

	// マウス座標を2Dレティクルのスプライトに代入する

	// ビュープロジェクションビューポート合成行列
	Matrix4x4 matViewport = MatrixFunction::MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	Matrix4x4 matVPV = _viewProjection.matView * _viewProjection.matProjection * matViewport;
	// 合成行列の逆行列を計算する
	Matrix4x4 matInverseVPV = MatrixFunction::Inverse(matVPV);

	// スクリーン座標
	Vector3 posNear = Vector3((float)spritePosition.x, spritePosition.y, 0);
	Vector3 posFar = Vector3((float)spritePosition.x, spritePosition.y, 1);

	// スクリーンからワールドへ
	posNear = VectorFunction::Transform(posNear, matInverseVPV);
	posFar = VectorFunction::Transform(posFar, matInverseVPV);

	// マウスレイの方向
	Vector3 reticleDirection = posFar - posNear;
	reticleDirection = VectorFunction::Normalize(reticleDirection);

	// カメラから標準オブジェクトへの距離
	const float kDistanceTestObject = 50.0f;
	woldTransform3DReticle.translation_ = posNear + reticleDirection * kDistanceTestObject;

	woldTransform3DReticle.UpdateMatrix();

	ImGui::Begin("Reticle");
	ImGui ::Text("2DReticle:(%f,%f)", spritePosition.x, spritePosition.y);
	ImGui ::Text("Near:(%+.2f,%+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
	ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);
	ImGui::Text("3DReticle:(%+.2f,%+.2f,%+.2f)", woldTransform3DReticle.translation_.x, woldTransform3DReticle.translation_.y, woldTransform3DReticle.translation_.z);
	ImGui::End();
}

void Player::ImGui() {
	ImGui::Begin("Player");
	ImGui::DragFloat3("Scale", &worldTransform.scale_.x, 0.1f);
	ImGui::DragFloat3("Rotation", &worldTransform.rotation_.x, 0.1f);
	ImGui::DragFloat3("Translation", &worldTransform.translation_.x, 0.1f);
	ImGui::End();
}
