#pragma once
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>
#include "Sprite.h"

class Player {
public:
	~Player();

	void Initialize(Model* _model, uint32_t _textrueHandle, uint32_t _reticleTextrueHandle, const Vector3& _pos = {0, 0, 0});
	void Update(ViewProjection& _viewProjection);
	void Draw(ViewProjection& _viewProjection);
	void DrawUI();

	Vector3 GetWorldPositoin();
	Vector3 Get3DReticleWorldPositoin();
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

	void Update3DReticle();
	void Update2DReticle(ViewProjection& _viewProjection);

	WorldTransform worldTransform;
	Model* model = nullptr;
	uint32_t textureHandle = 0;

	Input* input = nullptr;

	const float kRotSpeed = 0.02f;      // 回転の速さ
	const float kCharacterSpeed = 0.1f; // キャラクターの速さ

	const float radius = 2.0f;

	std::list<PlayerBullet*> bullets;

	WorldTransform woldTransform3DReticle;
	uint32_t texture3DReticle = 0;
	Sprite* sprite2DReticle = nullptr;


#ifdef _DEBUG
	void ImGui();
#endif // _DEBUG
};