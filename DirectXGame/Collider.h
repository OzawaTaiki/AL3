#pragma once
#include "VectorFunction.h"
#include <cstdint>

class Collider {
public:
	float GetRadius() { return radius; };
	void SetRadius(float _radius) { radius = _radius; };

	virtual void OnCollision(){};

	virtual Vector3 GetWorldPosition() = 0;

	uint32_t GetCollisionAttribute() { return collisionAtrribute; };
	void SetCollisionAttribute(uint32_t _attribute) { collisionAtrribute = _attribute; };
	uint32_t GetCollisionMask() { return collisionMask; };
	void SetCollisionMask(uint32_t _Mask) { collisionMask = _Mask; };

private:
	float radius = 1.1f;

	uint32_t collisionAtrribute = 0xffffffff;
	uint32_t collisionMask = 0xffffffff;
};
