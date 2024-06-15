#include "Enemy.h"
#include "ImGuiManager.h"
#include "VectorFunction.h"
#include <cassert>

void (Enemy::*Enemy::phaseTable[])() = {&Enemy::ApproachPhase, &Enemy::LeavePhase};

Enemy::~Enemy() {
	for (EnemyBullet* nBullet : bullets) {
		delete nBullet;
	}
	bullets.clear();

	for (TimedCall* TC : timedCall) {
		delete TC;
	}
	timedCall.clear();
}

void Enemy::Initialize(Model* _model, uint32_t _textrueHandle) {
	// NULLチェック
	assert(_model);
	model = _model;
	textureHandle = _textrueHandle;
	// ワールドトランス初期化
	worldTransform.Initialize();
	phase = phaseTable[(int)Phase::Approach];

	InitializeApproachPhase();
	ShootAndResetTimer();
}

void Enemy::Update() {

	bullets.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	(this->*Enemy::phase)();

	worldTransform.UpdateMatrix();

	timedCall.remove_if([](TimedCall* _timedCall) {
		if (_timedCall->IsFinished()) {
			delete _timedCall;
			return true;
		}
		return false;
	});

	for (TimedCall* TC : timedCall) {
		TC->Update();
	}

	for (EnemyBullet* nBullet : bullets) {
		nBullet->Update();
	}

	Imgui();
}

void Enemy::Draw(ViewProjection& _viewProjection) {
	model->Draw(worldTransform, _viewProjection, textureHandle);
	for (EnemyBullet* nBullet : bullets) {
		nBullet->Draw(_viewProjection);
	}
}

void Enemy::SetTranslete(const Vector3& _translation) { worldTransform.translation_ = _translation; }

void Enemy::InitializeApproachPhase() { fireTimer = kFireInterval; }

void Enemy::UpdateApproachPhase() { ShootAndResetTimer(); }

void Enemy::ShootAndResetTimer() {

	// timedCallが空でない場合、つまり前の発射の予約が存在する場合
	if (!timedCall.empty()) {
		// 最後のTimedCallオブジェクトが完了していない場合は何もしない
		if (!timedCall.back()->IsFinished()) {
			return;
		}
	}
	Fire();
	timedCall.push_back(new TimedCall(std::bind(&Enemy::ShootAndResetTimer, this), kFireInterval));
}

void Enemy::Imgui() {
	ImGui::Begin("Enemy");
	ImGui::DragFloat3("Translation", &worldTransform.translation_.x, 0.1f);
	ImGui::Text("%s", phase == phaseTable[0] ? "Approach" : "Leave");
	ImGui::End();
}

void Enemy::LeavePhase() {
	Vector3 velocity = {0.3f, 0.2f, -0.2f};
	worldTransform.translation_ += velocity;
}
void Enemy::ApproachPhase() {

	Vector3 velocity(0, 0, -0.1f);
	worldTransform.translation_ += velocity;
	UpdateApproachPhase();
	if (worldTransform.translation_.z < -10.0f) {
		phase = phaseTable[(int)Phase::Leave];
	}
}

void Enemy::Fire() {
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, -kBulletSpeed);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->initialize(model, worldTransform.translation_, velocity);

	bullets.push_back(newBullet);
}
