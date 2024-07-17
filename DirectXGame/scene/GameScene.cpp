#include "GameScene.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection.Initialize();

	player_ = std::make_unique<Player>();
	playerModel_.push_back(Model::CreateFromOBJ("body", true));
	
	//playerModel_.reset(Model::CreateFromOBJ("playerModel", true));
	//player_->Initialize(playerModel_.get());

	skydoom_ = std::make_unique<Skydoom>();
	skydoomModel_.reset(Model::CreateFromOBJ("skydoom", true));
	skydoom_->Initialze(skydoomModel_.get());

	ground_ = std::make_unique<Ground>();
	groundModel_.reset(Model::CreateFromOBJ("ground", true));
	ground_->Initialize(groundModel_.get());

	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransform());

	player_->SetViewProjection(&followCamera_->GetViewProjection());

	debugCamera = std::make_unique<DebugCamera>(WinApp::kWindowWidth, WinApp::kWindowHeight);
}

void GameScene::Update() {
	if (input_->TriggerKey(DIK_0))
		debugCameraActive = debugCameraActive ? false : true;

	skydoom_->Update();
	ground_->Update();
	player_->Update();
	followCamera_->Update();

	if (debugCameraActive) {
		debugCamera->Update();
		viewProjection.matView = debugCamera->GetViewProjection().matView;
		viewProjection.matProjection = debugCamera->GetViewProjection().matProjection;
		viewProjection.TransferMatrix();
	} else {
		viewProjection.matView = followCamera_->GetViewProjection().matView;
		viewProjection.matProjection = followCamera_->GetViewProjection().matProjection;
		viewProjection.TransferMatrix();
	}
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

	skydoom_->Draw(viewProjection);
	ground_->Draw(viewProjection);
	player_->Draw(viewProjection);

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
