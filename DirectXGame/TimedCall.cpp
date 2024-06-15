#include "TimedCall.h"

TimedCall::TimedCall(std::function<void(void)> _func, uint32_t _time) : func(_func), time(_time){};

void TimedCall::Update() {
	if (isFinished) {
		return;
	}

	time--;
	if (time <= 0) {
		isFinished = true;
		func();
	}
};