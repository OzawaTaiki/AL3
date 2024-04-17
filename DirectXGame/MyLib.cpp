#include "MyLib.h"

template<typename T> T MyLib::clamp(T value, T min, T max) { return (value < min) ? min : (value > max) ? max : value; }