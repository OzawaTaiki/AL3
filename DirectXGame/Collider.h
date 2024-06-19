#pragma once
#include "VectorFunction.h"

class Collider {
public:
	float GetRadius() { return radius; };
	void SetRadius(float _radius) { radius = _radius; };

	virtual void OnCollision(){};

	virtual Vector3 GetWorldPosition() = 0;

private:

	float radius = 1.1f;
};
