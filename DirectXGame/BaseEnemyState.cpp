#include "BaseEnemyState.h"
#include <Windows.h>

void BaseEnemyState::DebugLog() { OutputDebugStringA(name.c_str()); }