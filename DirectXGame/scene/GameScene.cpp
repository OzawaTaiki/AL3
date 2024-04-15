#include "GameScene.h"
#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite;
	delete model;
	delete debugCamera;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textueHandle = TextureManager::Load("uvChecker.png");
	soundDataHandle = soundDataHandle = audio_->LoadWave("fanfare.wav");

	sprite = Sprite::Create(textueHandle, {100, 50});
	model = Model::Create();

	worldTransform.Initialize();
	viewProjection.Initialize();

	// audio_->PlayWave(soundDataHandle);
	voiceHandle = audio_->PlayWave(soundDataHandle, true);

	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection);

	debugCamera = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	AxisIndicator::GetInstance()->SetVisible(1);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera->GetViewProjection());
}

void GameScene::Update() {

	Vector2 position = sprite->GetPosition();
	position.y += 1.0f;
	if (position.y > WinApp::kWindowHeight)
		position.y = 64.0f;
	sprite->SetPosition(position);
	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(voiceHandle);
	}
#ifdef _DEBUG

	// ImGui::Text("kamata tarou %d,%d,%d", 2050, 12, 31);
	ImGui::Begin("Debug1");
	ImGui::Text("kamata tarou %d,%d,%d", 2050, 12, 31);
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::End();
	// ImGui::ShowDemoWindow();
#endif // _DEBUG

	debugCamera->Update();
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

	model->Draw(worldTransform, debugCamera->GetViewProjection(), textueHandle);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	sprite->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
