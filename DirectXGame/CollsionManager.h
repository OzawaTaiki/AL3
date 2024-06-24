#pragma once
#include "Collider.h"
#include <list>

class CollsionManager {
public:
	void SetCollider(Collider* _collider);
	void ListReset();

	void CheckAllCollisions();

private:
	void CheckCollisionPair(Collider* _colliderA, Collider* _colliderB);

	std::list<Collider*> colliders;
};