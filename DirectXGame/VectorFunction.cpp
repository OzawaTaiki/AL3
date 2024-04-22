#include "VectorFunction.h"
#include <cassert>
#include <cmath>

static const int kColumnWidth = 60;

Vector3 VectorFunction::Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

Vector3 VectorFunction::Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

Vector3 VectorFunction::Multiply(float scalar, const Vector3& v) {
	Vector3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;

	return result;
}

Vector3 VectorFunction::Multiply(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;

	return result;
}

float VectorFunction::Dot(const Vector3& v1, const Vector3& v2) {
	float result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return result;
}

Vector3 VectorFunction::Cross(const Vector3& _v1, const Vector3& _v2) {
	Vector3 result;

	result.x = _v1.y * _v2.z - _v1.z * _v2.y;
	result.y = _v1.z * _v2.x - _v1.x * _v2.z;
	result.z = _v1.x * _v2.y - _v1.y * _v2.x;

	return result;
}

float VectorFunction::length(const Vector3& v) {
	float result;
	result = std::sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}

Vector3 VectorFunction::Normalize(const Vector3& v) {
	Vector3 result;
	float lenght = length(v);
	if (lenght == 0)
		return {0, 0, 0};

	result.x = v.x / lenght;
	result.y = v.y / lenght;
	result.z = v.z / lenght;

	return result;
}

Vector3 VectorFunction::Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

void VectorFunction::Clamp(Vector3& _value, const Vector3& _min, const Vector3& _max) {
	_value.x = (_value.x < _min.x) ? _min.x : (_value.x > _max.x) ? _max.x : _value.x;
	_value.y = (_value.y < _min.y) ? _min.y : (_value.y > _max.y) ? _max.y : _value.y;
	_value.z = (_value.z < _min.z) ? _min.z : (_value.z > _max.z) ? _max.z : _value.z;
}

Vector3 VectorFunction::TransformNormal(const Vector3& _v, const Matrix4x4& _m) {
	Vector3 result{
	    _v.x * _m.m[0][0] + _v.y * _m.m[1][0] + _v.z * _m.m[2][0] + 1.0f * _m.m[3][0], _v.x * _m.m[0][1] + _v.y * _m.m[1][1] + _v.z * _m.m[2][1] + 1.0f * _m.m[3][1],
	    _v.x * _m.m[0][2] + _v.y * _m.m[1][2] + _v.z * _m.m[2][2] + 1.0f * _m.m[3][2]};
	return result;
}

Vector3& operator+=(Vector3& _v1, const Vector3& _v2) { return _v1 = Vector3(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.z); }

Vector3& operator-=(Vector3& _v1, const Vector3& _v2) { return _v1 = Vector3(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z); }
