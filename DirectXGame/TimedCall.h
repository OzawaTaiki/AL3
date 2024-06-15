#pragma once

#include <functional>

class TimedCall {
public:
	TimedCall(std::function<void(void)> _func, uint32_t _time);
	void Update();

	bool IsFinished() { return isFinished; };

private:
	// コールバック
	std::function<void(void)> func;
	// 残り時間
	uint32_t time;
	// 完了フラグ
	bool isFinished = false;
};