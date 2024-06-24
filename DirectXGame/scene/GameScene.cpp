#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete playerModel;
	delete player;
	delete enemy;
	delete debugCamera;
	delete collsionManager;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	playerTextrueHandle = TextureManager::Load("uvChecker.png");
	enemyTextrueHandle = TextureManager::Load("axis/axis.jpg");

	playerModel = Model::Create();
	enemyModel = Model::Create();

	viewProjection.Initialize();

	player = new Player();
	player->Initialize(playerModel, playerTextrueHandle);

	enemy = new Enemy();
	enemy->Initialize(enemyModel, enemyTextrueHandle);
	enemy->SetTranslete(Vector3(5, 2, 20));

	enemy->SetPlayer(player);

	debugCamera = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	AxisIndicator::GetInstance()->SetVisible(1);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection);

	collsionManager = new CollsionManager;
}

void GameScene::Update() {
#ifdef _DEBUG
	if (input_->PushKey(DIK_0))
		debugCameraActive = debugCameraActive ? false : true;
	if (input_->PushKey(DIK_1))
		enemy->SetTranslete(Vector3(5, 2, 20));

#endif // _DEBUG

	collsionManager->ListReset();

	player->Update();
	collsionManager->SetCollider(player);
	for (Collider* pBullet : player->GetBullets()) {
		collsionManager->SetCollider(pBullet);
	}

	if (enemy) {
		enemy->Update();
		collsionManager->SetCollider(enemy);
		for (Collider* eBullet : enemy->GetBullets()) {
			collsionManager->SetCollider(eBullet);
		}
	}
	if (debugCameraActive) {
		debugCamera->Update();
		viewProjection.matView = debugCamera->GetViewProjection().matView;
		viewProjection.matProjection = debugCamera->GetViewProjection().matProjection;
		viewProjection.TransferMatrix();
	} else {
		viewProjection.UpdateMatrix();
	}

	collsionManager->CheckAllCollisions();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player->Draw(viewProjection);
	if (enemy)
		enemy->Draw(viewProjection);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
