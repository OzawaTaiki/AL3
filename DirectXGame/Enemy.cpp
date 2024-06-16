#include "Enemy.h"
#include "ImGuiManager.h"
#include "Player.h"
#include "VectorFunction.h"
#include <cassert>

void (Enemy::*Enemy::phaseTable[])() = {&Enemy::ApproachPhase, &Enemy::LeavePhase};

Enemy::~Enemy() {
	for (EnemyBullet* nBullet : bullets) {
		delete nBullet;
	}
	bullets.clear();
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
}

void Enemy::Update() {

	bullets.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	//(this->*Enemy::phase)();

	worldTransform.UpdateMatrix();

	UpdateApproachPhase();

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

void Enemy::UpdateApproachPhase() {
	fireTimer--;
	if (fireTimer <= 0) {
		Fire();
		fireTimer = kFireInterval;
	}
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform.matWorld_.m[3][0];
	worldPos.y = worldTransform.matWorld_.m[3][1];
	worldPos.z = worldTransform.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::Imgui() {
	ImGui::Begin("Enemy");
	ImGui::DragFloat3("Translation", &worldTransform.translation_.x, 0.1f);
	ImGui::Text("%s", phase == phaseTable[0] ? "Approach" : "Leave");
	ImGui::End();
}

void Enemy::LeavePhase() {
	Vector3 velocity = {0, 0, -0.3f};
	worldTransform.translation_ -= velocity;
}
void Enemy::ApproachPhase() {

	Vector3 velocity(0, 0, -0.1f);
	worldTransform.translation_ += velocity;
	if (worldTransform.translation_.z < 0.0f) {
		// phase = phaseTable[(int)Phase::Leave];
	}
}

void Enemy::Fire() {
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, -kBulletSpeed);

	Vector3 pPos = player->GetWorldPositoin();
	Vector3 ePos = GetWorldPosition();

	Vector3 e2pVect = pPos - ePos;
	Vector3 normVect = VectorFunction::Normalize(e2pVect);
	velocity = normVect * kBulletSpeed;

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->initialize(model, worldTransform.translation_, velocity);

	bullets.push_back(newBullet);
}
