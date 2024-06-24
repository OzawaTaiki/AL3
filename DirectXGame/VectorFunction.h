#pragma once
#include <Matrix4x4.h>
#include <Vector3.h>

class VectorFunction {
public:
	static Vector3 Add(const Vector3& v1, const Vector3& v2);
	static Vector3 Subtract(const Vector3& v1, const Vector3& v2);
	static Vector3 Multiply(float scalar, const Vector3& v);
	static Vector3 Multiply(const Vector3& v1, const Vector3& v2);
	static float Dot(const Vector3& v1, const Vector3& v2);
	static Vector3 Cross(const Vector3& _v1, const Vector3& _v2);
	static float length(const Vector3& v);
	static Vector3 Normalize(const Vector3& v);
	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
	static Vector3 Lerp(const Vector3& _vector1, const Vector3& _vector2, float _t);

	static void Clamp(Vector3& _value, const Vector3& _min, const Vector3& _max);
	static Vector3 TransformNormal(const Vector3& _v, const Matrix4x4& _m);
};

Vector3& operator+=(Vector3& _v1, const Vector3& _v2);
Vector3& operator-=(Vector3& _v1, const Vector3& _v2);
Vector3 operator+(const Vector3& _v1, const Vector3& _v2);
Vector3 operator-(const Vector3& _v1, const Vector3& _v2);
Vector3 operator*(const Vector3& _v1, const Vector3& _v2);
Vector3 operator/(const Vector3& _v1, const Vector3& _v2);
Vector3 operator*(const Vector3& _v, float _s);
Vector3 operator/(const Vector3& _v, float _s);
Vector3 operator*(float _s, const Vector3& _v);
Vector3 operator/(float _s, const Vector3& _v);
Vector3 operator-(const Vector3& _v);