#include "Enemy.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "Player.h"
#include "VectorFunction.h"
#include <cassert>

int Enemy::num = 0;

void (Enemy::*Enemy::phaseTable[])() = {&Enemy::ApproachPhase, &Enemy::LeavePhase};

Enemy::~Enemy() {}

void Enemy::Initialize(Model* _model, uint32_t _textrueHandle) {
	// NULLチェック
	assert(_model);
	model = _model;
	textureHandle = _textrueHandle;
	// ワールドトランス初期化
	worldTransform.Initialize();
	phase = phaseTable[(int)Phase::Approach];
	isAlive = true;
	isStop = false;
	InitializeApproachPhase();
}

void Enemy::Update() {
	if (!isAlive)
		return;

	if (!isStop)
		(this->*Enemy::phase)();

	worldTransform.UpdateMatrix();


	Imgui();
}

void Enemy::Draw(ViewProjection& _viewProjection) {
	if (isAlive)
		model->Draw(worldTransform, _viewProjection, textureHandle);
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

void Enemy::OnCollision() { isAlive = false; }

void Enemy::Imgui() {

	std::string title = "Enemy" + std::to_string(num++);

	ImGui::SetNextWindowSize(ImVec2(300, 100));
	ImGui::Begin(title.c_str());
	ImGui::DragFloat3("Translation", &worldTransform.translation_.x, 0.1f);
	ImGui::Text("%s", phase == phaseTable[0] ? "Approach" : "Leave");
	ImGui::Checkbox("IsStop", &isStop);
	ImGui::End();
}

void Enemy::LeavePhase() {
	Vector3 velocity = {0.3f, 0.3f, 0.0f};
	worldTransform.translation_ += velocity;
}
void Enemy::ApproachPhase() {

	Vector3 velocity(0, 0, -0.1f);
	worldTransform.translation_ += velocity;
	if (worldTransform.translation_.z < 0.0f) {
		phase = phaseTable[(int)Phase::Leave];
	}
	UpdateApproachPhase();
}

void Enemy::Fire() {
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, -kBulletSpeed);

	Vector3 pPos = player->GetWorldPositoin();
	Vector3 ePos = worldTransform.translation_;

	Vector3 e2pVect = pPos - ePos;
	Vector3 normVect = VectorFunction::Normalize(e2pVect);
	velocity = normVect * kBulletSpeed;

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->initialize(model, worldTransform.translation_, velocity);

	if (gameScene)
		gameScene->AddEnemyBullet(newBullet);
}

Vector3 Enemy::GetWorldPositoin() {
	Vector3 worldPos;

	worldPos.x = worldTransform.matWorld_.m[3][0];
	worldPos.y = worldTransform.matWorld_.m[3][1];
	worldPos.z = worldTransform.matWorld_.m[3][2];

	return worldPos;
}
