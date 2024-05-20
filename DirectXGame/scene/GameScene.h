#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "RailCamera.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "skydoom.h"
#include <sstream>

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

	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	/// <param name="_enemyBullet">敵弾</param>
	void AddEnemyBullet(EnemyBullet* _enemyBullet);

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
	std::list<Enemy*> enemy;
	std::list<EnemyBullet*> enemyBullet;

	Skydoom* skydoom = nullptr;
	Model* modelSkydoom = nullptr;

	RailCamera* railCamera = nullptr;

	bool debugCameraActive = false;
	DebugCamera* debugCamera = nullptr;

	std::stringstream enemyPopCommands;

	//待機タイマー
	uint32_t enemyPopWaitTime;
	//待機中フラグ
	bool isWaiting;

	// 関数
	void CheckAllCollisions();

	void PopEnemy(const Vector3& _pos);

	void LoadEnemyPopData();

	void UpdataEnemyPopCommands();
};
