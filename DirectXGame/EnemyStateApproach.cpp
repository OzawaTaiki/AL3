#include "EnemyStateApproach.h"
#include "Enemy.h"
#include "EnemyStateLeave.h"

EnemyStateApproach::EnemyStateApproach(Enemy* _enemy) : BaseEnemyState("State Approach", _enemy) {}

void EnemyStateApproach::Update() {
	Vector3 velocity(0, 0, -0.1f);
	enemy->AddVelocity(velocity);
	if (enemy->GetWorldPos().z < 0.0f) {
		enemy->ChangeState(std::make_unique<EnemyStateLeave>(enemy));
	}
}
