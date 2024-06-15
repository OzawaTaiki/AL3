#include "EnemyStateLeave.h"
#include "Enemy.h"
#include "VectorFunction.h"

EnemyStateLeave::EnemyStateLeave(Enemy* _enemy) : BaseEnemyState("State Leave", _enemy) {}

void EnemyStateLeave::Update() {
	Vector3 velocity = {0.2f, 0.3f, 0.0f};
	enemy->AddVelocity(velocity);
}
