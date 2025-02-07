#include "StageScene.h"

#include "Novice.h"

constexpr uint32_t gridSize = 32;

void StageScene::Init() {
	this->inputHandler_ = std::make_unique<StageSceneInputHandler>();
}

void StageScene::Update([[maybe_unused]] std::vector<char>& keys, [[maybe_unused]] std::vector<char>& preKeys) {
	this->inputHandler_->UpdateKeyState();

	// get command type
	if (selector_->GetSelectMode() == SLECTOR) {
		this->command_ = inputHandler_->SelectorHandleInput(this->selector_);
	} else if (selector_->GetSelectMode() == UNIT) {
		this->command_ = inputHandler_->UnitHandleInput(selector_->GetSelectedUnitAddress());
	}

	//// 移動入力
	//if (keys[DIK_W]) {
	//	playerPos_.y -= playerMoveSpeed_;
	//}

	//if (keys[DIK_S]) {
	//	playerPos_.y += playerMoveSpeed_;
	//}

	//if (keys[DIK_A]) {
	//	playerPos_.x -= playerMoveSpeed_;
	//}

	//if (keys[DIK_D]) {
	//	playerPos_.x += playerMoveSpeed_;
	//}


	//// 敵が3回倒されたらクリア
	//if (enemyKillCount_ >= 3) {
	//	// クリアシーンに遷移
	//	sceneNo_ = SCENE_ID_CLEAR;
	//}
}

void StageScene::Draw() {
	// 画面左上からgridSize間隔でグリッドを描画
	for (uint32_t x = 0; x < KamataEngine::WinApp::kWindowWidth; x += gridSize) {
		for (uint32_t y = 0; y < KamataEngine::WinApp::kWindowHeight; y += gridSize) {
			Novice::DrawLine(x, 0, x, KamataEngine::WinApp::kWindowHeight, 0x212121FF); // 垂直線
			Novice::DrawLine(0, y, KamataEngine::WinApp::kWindowWidth, y, 0x212121FF); // 水平線
		}
	}
}