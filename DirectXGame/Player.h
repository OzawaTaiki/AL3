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

	void Initialize(Model* _model, uint32_t _textrueHandle);
	void Update();
	void Draw(ViewProjection& _viewProjection);

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
	const float kCharacterSpeed = 0.2f; // キャラクターの速さ

	std::list<PlayerBullet*> bullets;

#ifdef _DEBUG
	void ImGui();
#endif // _DEBUG
};