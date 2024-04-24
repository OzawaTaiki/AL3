#include "MyLib.h"

Vector3 Project(const Vector3& _v1, const Vector3& _v2)
{
	Vector3 normalize = VectorFunction::Normalize(_v2);

	Vector3 result = VectorFunction::Multiply(VectorFunction::Dot(_v1, normalize), normalize);

	return result;
}

Vector3 ClosestPoint(const Vector3& _point, const Segment& _segment)
{
	Vector3 cp = VectorFunction::Add(_segment.origin, Project(VectorFunction::Subtract(_point, _segment.origin), _segment.diff));

	return cp;
}

bool IsCollision(const Sphere& _s1, const Sphere& _s2)
{
	float distance = VectorFunction::length(VectorFunction::Subtract(_s1.center, _s2.center));
	return distance <= _s1.radius + _s2.radius ? true : false;
}

