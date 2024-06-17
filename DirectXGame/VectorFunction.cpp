#include "VectorFunction.h"
#include "MyLib.h"
#include <assert.h>
#include <cmath>

Vector3 Add(const Vector3& _v1, const Vector3& _v2) {
	Vector3 result;
	result.x = _v1.x + _v2.x;
	result.y = _v1.y + _v2.y;
	result.z = _v1.z + _v2.z;

	return result;
}

Vector3 Subtract(const Vector3& _v1, const Vector3& _v2) {
	Vector3 result;
	result.x = _v1.x - _v2.x;
	result.y = _v1.y - _v2.y;
	result.z = _v1.z - _v2.z;

	return result;
}

Vector3 Multiply(float _scalar, const Vector3& _v) {
	Vector3 result;
	result.x = _v.x * _scalar;
	result.y = _v.y * _scalar;
	result.z = _v.z * _scalar;

	return result;
}

Vector3 Multiply(const Vector3& _v1, const Vector3& _v2) {
	Vector3 result;
	result.x = _v1.x * _v2.x;
	result.y = _v1.y * _v2.y;
	result.z = _v1.z * _v2.z;

	return result;
}

float Dot(const Vector3& _v1, const Vector3& _v2) {
	float result = _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z;

	return result;
}

Vector3 Cross(const Vector3& _v1, const Vector3& _v2) {
	Vector3 result;

	result.x = _v1.y * _v2.z - _v1.z * _v2.y;
	result.y = _v1.z * _v2.x - _v1.x * _v2.z;
	result.z = _v1.x * _v2.y - _v1.y * _v2.x;

	return result;
}

float Length(const Vector3& _v) {
	float result;
	result = std::sqrtf(_v.x * _v.x + _v.y * _v.y + _v.z * _v.z);
	return result;
}

Vector3 Normalize(const Vector3& _v) {
	Vector3 result;
	float length = Length(_v);
	if (length == 0)
		return {0};
	result.x = _v.x / length;
	result.y = _v.y / length;
	result.z = _v.z / length;

	return result;
}

Vector3 Transform(const Vector3& _vector, const Matrix4x4& _matrix) {
	Vector3 result;

	result.x = _vector.x * _matrix.m[0][0] + _vector.y * _matrix.m[1][0] + _vector.z * _matrix.m[2][0] + 1.0f * _matrix.m[3][0];
	result.y = _vector.x * _matrix.m[0][1] + _vector.y * _matrix.m[1][1] + _vector.z * _matrix.m[2][1] + 1.0f * _matrix.m[3][1];
	result.z = _vector.x * _matrix.m[0][2] + _vector.y * _matrix.m[1][2] + _vector.z * _matrix.m[2][2] + 1.0f * _matrix.m[3][2];
	float _w = _vector.x * _matrix.m[0][3] + _vector.y * _matrix.m[1][3] + _vector.z * _matrix.m[2][3] + 1.0f * _matrix.m[3][3];
	assert(_w != 0.0f);
	result.x /= _w;
	result.y /= _w;
	result.z /= _w;
	return result;
}

Vector3 TransformNormal(const Vector3& _v, const Matrix4x4& _m) {
	Vector3 result{
	    _v.x * _m.m[0][0] + _v.y * _m.m[1][0] + _v.z * _m.m[2][0] + 1.0f * _m.m[3][0], _v.x * _m.m[0][1] + _v.y * _m.m[1][1] + _v.z * _m.m[2][1] + 1.0f * _m.m[3][1],
	    _v.x * _m.m[0][2] + _v.y * _m.m[1][2] + _v.z * _m.m[2][2] + 1.0f * _m.m[3][2]};
	return result;
}

void Clamp(Vector3& _value, const Vector3& _min, const Vector3& _max) {
	_value.x = (_value.x < _min.x) ? _min.x : (_value.x > _max.x) ? _max.x : _value.x;
	_value.y = (_value.y < _min.y) ? _min.y : (_value.y > _max.y) ? _max.y : _value.y;
	_value.z = (_value.z < _min.z) ? _min.z : (_value.z > _max.z) ? _max.z : _value.z;
}

Vector3 Lerp(const Vector3& _vector1, const Vector3& _vector2, float _t) {
	Vector3 result;
	result = _vector1 * (1.0f - _t) + _vector2 * _t;

	return result;
}

Vector3 Slerp(const Vector3& _vector1, const Vector3& _vector2, float _t) {

	Vector3 normalizeV1 = Normalize(_vector1);
	Vector3 normalizeV2 = Normalize(_vector2);

	float dot = Dot(normalizeV1, normalizeV2);

	dot = 1.0f < dot ? 1.0f : dot;
	dot = -1.0f > dot ? -1.0f : dot;

	float theta = std::acos(dot);

	float sinTheta = std::sin(theta);
	float sinThetaFrom = std::sin((1.0f - _t) * theta);
	float sinThetaTo = std::sin(_t * theta);

	Vector3 result;
	if (sinTheta < 1.0e-5) {
		result = normalizeV1;
	} else {
		result = (normalizeV1 * sinThetaFrom + normalizeV2 * sinThetaTo) / sinTheta;
	}

	float length1 = Length(_vector1);
	float length2 = Length(_vector2);

	float length = Lerp(length1, length2, _t);

	return Vector3(result * length);
}

Vector3 operator+(const Vector3& _v1, const Vector3& _v2) { return Vector3(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.z); }

Vector3 operator-(const Vector3& _v1, const Vector3& _v2) { return Vector3(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z); }

Vector3 operator*(const Vector3& _v1, const Vector3& _v2) { return Vector3(_v1.x * _v2.x, _v1.y * _v2.y, _v1.z * _v2.z); }

Vector3 operator/(const Vector3& _v1, const Vector3& _v2) { return Vector3(_v1.x / _v2.x, _v1.y / _v2.y, _v1.z / _v2.z); }

Vector3 operator*(const Vector3& _v, float _s) { return Vector3(_v.x * _s, _v.y * _s, _v.z * _s); }

Vector3 operator/(const Vector3& _v, float _s) { return Vector3(_v.x / _s, _v.y / _s, _v.z / _s); }

Vector3 operator-(const Vector3& _v) { return Vector3(-_v.x, -_v.y, -_v.z); }

Vector3& operator+=(Vector3& _v1, const Vector3& _v2) { return _v1 = Vector3(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.z); }

Vector3& operator-=(Vector3& _v1, const Vector3& _v2) { return _v1 = Vector3(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z); }
