#pragma once
#include "Model.h"
#include "VectorFunction.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class PlayerBullet {
public:
	void initialize(Model* _model, const Vector3& _position, const Vector3& _velocity, uint32_t _textrueHandle = 0);

	void Update();

	void Draw(const ViewProjection& _viewProjection);

	bool IsDead() const { return isDead; };
	Vector3 GetWorldPosition();

	void OnCollision();

	static const uint32_t kLifeTime = 60 * 5;

private:

	Model* model = nullptr;
	WorldTransform worldTransform;
	uint32_t textureHandle = 0;

	Vector3 velocity;
	int32_t deathTimer = kLifeTime;
	bool isDead = false;
};

/*

重大度レベル	コード	説明	プロジェクト	ファイル	行	抑制状態	詳細
エラー	LNK2019	未解決の外部シンボル "public: void __cdecl Player::OnCollision(void)" (?OnCollision@Player@@QEAAXXZ) が関数 "private: void __cdecl GameScene::CheckAllCollisions(void)"
(?CheckAllCollisions@GameScene@@AEAAXXZ) で参照されました	DirectXGame	C:\class\2年前期\AL3\AL3\DirectXGame\GameScene.obj	1


*/