#pragma once
#include "BaseEnemyState.h"

class EnemyStateApproach : public BaseEnemyState {
public:
	EnemyStateApproach(Enemy* _enemy);
	void Update();
};