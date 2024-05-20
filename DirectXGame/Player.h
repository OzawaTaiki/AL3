#pragma once
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>

class Player {
public:
	~Player();

	void Initialize(Model* _model, uint32_t _textrueHandle, const Vector3& _pos = {0, 0, 0});
	void Update();
	void Draw(ViewProjection& _viewProjection);

	Vector3 GetWorldPositoin();
	const std::list<PlayerBullet*>& GetBullets() const { return bullets; };

	void OnCollision();

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="_parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* _parent) { worldTransform.parent_ = _parent; };

private:
	// 旋回
	void rotate();
	// 射撃
	void Attack();

	WorldTransform worldTransform;
	Model* model = nullptr;
	uint32_t textureHandle = 0;

	Input* input = nullptr;

	const float kRotSpeed = 0.02f;      // 回転の速さ
	const float kCharacterSpeed = 0.1f; // キャラクターの速さ

	const float radius = 2.0f;

	std::list<PlayerBullet*> bullets;

#ifdef _DEBUG
	void ImGui();
#endif // _DEBUG
};