#include "MyLib.h"
#include "ImGuiManager.h"
#include <cmath>
#include <numbers>

float LerpShortAngle(float _a, float _b, float _t) {

	float diff = _b - _a;
	float rotate = std::fmod(diff, (float)std::numbers::pi * 2.0f);

	if (rotate > std::numbers::pi)
		rotate -= (float)std::numbers::pi * 2;
	else if (rotate < -std::numbers::pi)
		rotate += (float)std::numbers::pi * 2;

	return _a + rotate * _t;
}