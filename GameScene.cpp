#include "GameScene.h"

#include "Novice.h"

void GameScene::Init() {
	// プレイヤーの初期化
	playerRadius_ = 16.0f;
	playerPos_ = Vec2(
		KamataEngine::WinApp::kWindowWidth * 0.5f - playerRadius_ * 0.5f,
		static_cast<float>(KamataEngine::WinApp::kWindowHeight) - playerRadius_ * 2.0f
	);

	playerMoveSpeed_ = 8.0f;
	isPlayerShooting_ = false;

	// プレイヤー弾の初期化
	bulletRadius_ = 8.0f;
	// 画面外においておく
	bulletPos_ = Vec2(
		-bulletRadius_,
		-bulletRadius_
	);
	bulletMoveSpeed_ = 8.0f;

	// 敵の初期化
	enemyRadius_ = 16.0f;
	enemyPos_ = Vec2(
		static_cast<float>(KamataEngine::WinApp::kWindowWidth) * 0.5f - enemyRadius_ * 0.5f,
		enemyRadius_ * 2.0f
	);
	enemyMoveSpeed_ = 2.0f;
	enemyRespawnTimer = 120;
	isEnemyAlive_ = true;
	isEnemyExplosion_ = false;


	// 爆発テクスチャの読み込み
	ghExplode_ = Novice::LoadTexture("./Resources/explode.png");

	// 敵を倒した数の初期化
	enemyKillCount_ = 0;
}

void GameScene::Update([[maybe_unused]] std::vector<char>& keys, [[maybe_unused]] std::vector<char>& preKeys) {
	// 移動入力
	if (keys[DIK_W]) {
		playerPos_.y -= playerMoveSpeed_;
	}

	if (keys[DIK_S]) {
		playerPos_.y += playerMoveSpeed_;
	}

	if (keys[DIK_A]) {
		playerPos_.x -= playerMoveSpeed_;
	}

	if (keys[DIK_D]) {
		playerPos_.x += playerMoveSpeed_;
	}

	// 画面端より先に行かないようにする
	playerPos_.Clamp(
		Vec2(playerRadius_, playerRadius_),
		Vec2(static_cast<float>(KamataEngine::WinApp::kWindowWidth) - playerRadius_, static_cast<float>(KamataEngine::WinApp::kWindowHeight) - playerRadius_)
	);

	// 弾の発射
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		if (!isPlayerShooting_) {
			// 弾の初期位置をプレイヤーの中心に設定
			bulletPos_ = playerPos_;
			isPlayerShooting_ = true;
		}
	}

	// プレイヤー弾の処理
	if (isPlayerShooting_) {
		// 弾の移動
		bulletPos_.y -= bulletMoveSpeed_;

		// 画面外に出たら弾の発射を終了
		if (bulletPos_.y < -bulletRadius_) {
			isPlayerShooting_ = false;
		}

		// 敵が生きている場合のみ当たり判定を行う
		if (isEnemyAlive_) {
			// 弾と敵の当たり判定
			if (bulletPos_.Distance(enemyPos_) <= bulletRadius_ + enemyRadius_) {
				isEnemyAlive_ = false;
				isEnemyExplosion_ = true;
				isPlayerShooting_ = false;

				// 敵を倒した数をカウント
				enemyKillCount_++;
			}
		}
	}

	// 敵の処理
	if (isEnemyAlive_) {
		// 敵の移動
		enemyPos_.x += enemyMoveSpeed_;

		// 画面端に到達したら反転
		if (enemyPos_.x < enemyRadius_ || enemyPos_.x > KamataEngine::WinApp::kWindowWidth - enemyRadius_) {
			enemyMoveSpeed_ = -enemyMoveSpeed_;
		}

	} else {
		enemyRespawnTimer--;

		if (enemyRespawnTimer >= 90) {
			isEnemyExplosion_ = true;
		} else {
			isEnemyExplosion_ = false;
		}

		// 2秒後に敵を復活させる
		if (enemyRespawnTimer <= 0) {


			enemyPos_ = Vec2(
				static_cast<float>(KamataEngine::WinApp::kWindowWidth) * 0.5f - enemyRadius_ * 0.5f,
				enemyRadius_ * 2.0f
			);
			enemyMoveSpeed_ = 2.0f;
			enemyRespawnTimer = 120;
			isEnemyAlive_ = true;
			isEnemyExplosion_ = false;
		}
	}

	// 敵が3回倒されたらクリア
	if (enemyKillCount_ >= 3) {
		// クリアシーンに遷移
		sceneNo_ = SCENE_ID_CLEAR;
	}
}

void GameScene::Draw() {
	// 弾の発射中のみ描画
	if (isPlayerShooting_) {
		Novice::DrawTriangle(
			static_cast<int>(bulletPos_.x), static_cast<int>(bulletPos_.y - bulletRadius_),
			static_cast<int>(bulletPos_.x - bulletRadius_), static_cast<int>(bulletPos_.y + bulletRadius_),
			static_cast<int>(bulletPos_.x + bulletRadius_), static_cast<int>(bulletPos_.y + bulletRadius_),
			WHITE,
			kFillModeSolid
		);
	}

	// 敵が爆発していたら爆発テクスチャを描画
	if (isEnemyExplosion_) {
		Novice::DrawSprite(
			static_cast<int>(enemyPos_.x - enemyRadius_),
			static_cast<int>(enemyPos_.y - enemyRadius_),
			ghExplode_,
			1.0f, 1.0f,
			0.0f,
			WHITE
		);
	}

	// 敵が生きている場合のみ描画
	if (isEnemyAlive_) {
		Novice::DrawEllipse(
			static_cast<int>(enemyPos_.x), static_cast<int>(enemyPos_.y),
			static_cast<int>(enemyRadius_), static_cast<int>(enemyRadius_),
			0.0f,
			RED,
			kFillModeSolid
		);
	}

	// プレイヤーの描画
	Novice::DrawEllipse(
		static_cast<int>(playerPos_.x), static_cast<int>(playerPos_.y),
		static_cast<int>(playerRadius_), static_cast<int>(playerRadius_),
		0.0f,
		WHITE,
		kFillModeSolid
	);

	/* -------- デバッグ用 -------- */

	Novice::ScreenPrintf(0, 32, "pos:  %f %f", playerPos_.x, playerPos_.y);

	Novice::ScreenPrintf(16, 64, "WASD...Move");

	Novice::ScreenPrintf(16, 100, "enemyRespawnTimer...%d", enemyRespawnTimer);
	Novice::ScreenPrintf(16, 116, "isPlayerShooting...%d", isPlayerShooting_);
	Novice::ScreenPrintf(16, 132, "isEnemyAlive...%d", isEnemyAlive_);

	if (isPlayerShooting_) {
		Novice::DrawEllipse(
			static_cast<int>(bulletPos_.x), static_cast<int>(bulletPos_.y),
			static_cast<int>(bulletRadius_), static_cast<int>(bulletRadius_),
			0.0f,
			BLUE,
			kFillModeWireFrame
		);

		Novice::DrawLine(
			static_cast<int>(bulletPos_.x), static_cast<int>(bulletPos_.y),
			static_cast<int>(enemyPos_.x), static_cast<int>(enemyPos_.y),
			WHITE
		);

		Novice::DrawLine(
			static_cast<int>(bulletPos_.x), static_cast<int>(bulletPos_.y),
			static_cast<int>(enemyPos_.x), static_cast<int>(enemyPos_.y),
			WHITE
		);

		Novice::DrawLine(
			static_cast<int>(bulletPos_.x), static_cast<int>(bulletPos_.y),
			static_cast<int>(enemyPos_.x), static_cast<int>(enemyPos_.y),
			WHITE
		);
	}
}