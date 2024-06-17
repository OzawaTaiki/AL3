#include "MyLib.h"

float Lerp(float _point1, float _point2, float _t) { return (1.0f - _t) * _point1 + _t * _point2; }
