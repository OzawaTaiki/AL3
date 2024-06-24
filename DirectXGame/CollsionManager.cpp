#include "CollsionManager.h"

void CollsionManager::SetCollider(Collider* _collider) { colliders.push_back(_collider); }

void CollsionManager::ListReset() { colliders.clear(); }

void CollsionManager::CheckAllCollisions() {

	std::list<Collider*>::iterator itrA = colliders.begin();
	for (; itrA != colliders.end(); itrA++) {
		Collider* colliderA = *itrA;

		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders.end(); itrB++) {
			Collider* colliderB = *itrB;
			CheckCollisionPair(colliderA, colliderB);
		}
	}

	/*const std::list<PlayerBullet*>& playerBullets = player->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy->GetBullets();

#pragma region 自機と敵弾の衝突判定
	for (EnemyBullet* bullet : enemyBullets) {
	    CheckCollisionPair(player, bullet);
	}
#pragma endregion

#pragma region 自弾と敵の衝突判定
	for (PlayerBullet* bullet : playerBullets) {
	    CheckCollisionPair(bullet, enemy);
	}
#pragma endregion

#pragma region 自機と敵弾の衝突判定
	for (PlayerBullet* pBullet : playerBullets) {
	    for (EnemyBullet* eBullet : enemyBullets) {
	        CheckCollisionPair(pBullet, eBullet);
	    }
	}

#pragma endregion
*/
}

void CollsionManager::CheckCollisionPair(Collider* _colliderA, Collider* _colliderB) {

	if (!(_colliderA->GetCollisionAttribute() & _colliderB->GetCollisionMask()) || !(_colliderA->GetCollisionMask() & _colliderB->GetCollisionAttribute()))
		return;
	Vector3 worldPosisionColliderA = _colliderA->GetWorldPosition();
	Vector3 worldPosisionColliderB = _colliderB->GetWorldPosition();

	float radiusColliderA = _colliderA->GetRadius();
	float radiusColliderB = _colliderB->GetRadius();

	float distance = VectorFunction::length(worldPosisionColliderA - worldPosisionColliderB);

	if (distance < radiusColliderA + radiusColliderB) {
		_colliderA->OnCollision();
		_colliderB->OnCollision();
	}
}
