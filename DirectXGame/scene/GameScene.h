#pragma once

#include "Audio.h"
#include "Collider.h"
#include "CollsionManager.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// テクスチャハンドル
	uint32_t playerTextrueHandle = 0;
	uint32_t enemyTextrueHandle = 0;

	// 3Dモデルデータ
	Model* playerModel = nullptr;
	Model* enemyModel = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection;

	Player* player = nullptr;
	Enemy* enemy = nullptr;

	CollsionManager* collsionManager = nullptr;

	bool debugCameraActive = false;
	DebugCamera* debugCamera = nullptr;
};