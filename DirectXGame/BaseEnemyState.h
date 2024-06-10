#pragma once
#include <string>

class Enemy;

// 敵の状態基底
class BaseEnemyState {
public:
	BaseEnemyState(const std::string& _name, Enemy* _enemy) : name(_name), enemy(_enemy){};

	// 毎フレーム処理(純粋仮想関数)
	virtual void Update() = 0;

	// デバッグログ出カ
	virtual void DebugLog();

protected:
	// 状態名
	std::string name;
	// 操作対象の敵
	Enemy* enemy = nullptr;
};