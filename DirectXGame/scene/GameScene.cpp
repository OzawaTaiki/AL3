#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete playerModel;
	delete player;
	delete enemyModel;
	delete debugCamera;
	delete skydoom;
	delete modelSkydoom;
	for (Enemy* nEnemy : enemy) {
		delete nEnemy;
	}
	for (EnemyBullet* nBullet : enemyBullet) {
		delete nBullet;
	}
	enemyBullet.clear();
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

	railCamera = new RailCamera();
	Vector3 railCameraPos = {0, 3.0f, 0};
	Vector3 railCameraRota = {0.26f, 0, 0};
	railCamera->Initialize(railCameraPos, railCameraRota);

	skydoom = new Skydoom();
	modelSkydoom = Model::CreateFromOBJ("skydoom", true);
	skydoom->Initialze(modelSkydoom);

	player = new Player();
	Vector3 playerPos(0, 0, 15.0f);
	player->Initialize(playerModel, playerTextrueHandle, playerPos);
	player->SetParent(&railCamera->GetWorldTransform());

	debugCamera = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	AxisIndicator::GetInstance()->SetVisible(1);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection);

	enemyPopWaitTime = 120;
	isWaiting = true;
	LoadEnemyPopData();
}

void GameScene::Update() {
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0))
		debugCameraActive = debugCameraActive ? false : true;
		// if (input_->PushKey(DIK_1))
		//	enemy->SetTranslete(Vector3(5, 2, 20));

#endif // _DEBUG

	Vector3 railCameraPos = {0, 0, 0};
	Vector3 railCameraRota = {0.0f, 0.00f, 0};
	railCamera->Update(railCameraPos, railCameraRota);

	skydoom->Update();

	player->Update();

	for (Enemy* nEnemy : enemy) {
		nEnemy->Update();
	}
	for (EnemyBullet* nBullet : enemyBullet) {
		nBullet->Update();
	}
	enemyBullet.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	UpdataEnemyPopCommands();

	if (debugCameraActive) {
		debugCamera->Update();
		viewProjection.matProjection = debugCamera->GetViewProjection().matProjection;
		viewProjection.matView = debugCamera->GetViewProjection().matView;
		viewProjection.TransferMatrix();
	} else {
		viewProjection.matProjection = railCamera->GetViewProjectoin().matProjection;
		viewProjection.matView = railCamera->GetViewProjectoin().matView;
		viewProjection.TransferMatrix();
	}

	CheckAllCollisions();
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

	skydoom->Draw(viewProjection);

	player->Draw(viewProjection);
	for (Enemy* nEnemy : enemy) {
		nEnemy->Draw(viewProjection);
	}
	for (EnemyBullet* nBullet : enemyBullet) {
		nBullet->Draw(viewProjection);
	}

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

void GameScene::AddEnemyBullet(EnemyBullet* _enemyBullet) { enemyBullet.push_back(_enemyBullet); }

void GameScene::CheckAllCollisions() {

	const float playerSize = 1.1f;
	const float enemySize = 1.1f;
	const float playerBulletSize = 1.1f;
	const float enemyBulletSize = 1.1f;
	Vector3 posA, posB;

	const std::list<PlayerBullet*>& playerBullets = player->GetBullets();

	float distance = 0;

#pragma region 自機と敵弾の衝突判定
	posA = player->GetWorldPositoin();
	for (EnemyBullet* bullet : enemyBullet) {
		posB = bullet->GetWorldPositoin();

		distance = VectorFunction::length(posA - posB);
		if (distance < playerSize + enemyBulletSize) {
			player->OnCollision();
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵の衝突判定
	for (Enemy* nEnemy : enemy) {
		posA = nEnemy->GetWorldPositoin();
		for (PlayerBullet* bullet : playerBullets) {
			posB = bullet->GetWorldPositoin();

			distance = VectorFunction::length(posA - posB);
			if (distance < enemySize + playerBulletSize) {
				nEnemy->OnCollision();
				bullet->OnCollision();
			}
		}
	}
#pragma endregion

#pragma region 自機と敵弾の衝突判定
	for (PlayerBullet* pBullet : playerBullets) {
		posA = pBullet->GetWorldPositoin();

		for (EnemyBullet* eBullet : enemyBullet) {
			posB = eBullet->GetWorldPositoin();

			distance = VectorFunction::length(posA - posB);
			if (distance < enemyBulletSize + playerBulletSize) {
				pBullet->OnCollision();
				eBullet->OnCollision();
			}
		}
	}

#pragma endregion
}
void GameScene::LoadEnemyPopData() {
	// ファイルを開く
	std::ifstream file;
	file.open("Resources/data/enemyPopData.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GameScene::PopEnemy(const Vector3& _pos) {
	enemy.push_back(new Enemy());
	enemy.back()->Initialize(enemyModel, enemyTextrueHandle);
	enemy.back()->SetTranslete(_pos);
	enemy.back()->SetGameScene(this);
	enemy.back()->SetPlayer(player);
}

void GameScene::UpdataEnemyPopCommands() {

	if (isWaiting) {
		enemyPopWaitTime--;
		if (enemyPopWaitTime <= 0) {
			isWaiting = false;
		}
		return;
	}

	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {

		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}

		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			PopEnemy(Vector3(x, y, z));
		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			isWaiting = true;
			enemyPopWaitTime = waitTime;

			// コマンドループを抜ける 重要！！！！
			break;
		}
	}
}