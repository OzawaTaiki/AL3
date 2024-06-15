#include "BaseEnemyState.h"
#include <Windows.h>

std::string BaseEnemyState::DebugLog() {
	OutputDebugStringA(name.c_str());
	return name;
}