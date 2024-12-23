#include "GameManager.h"

#include <vector>

#include "ClearScene.h"
#include "GameScene.h"
#include "Novice.h"
#include "TitleScene.h"

GameManager::GameManager() {
	sceneArr_.resize(SCENE_ID_MAX);
	sceneArr_[SCENE_ID_TITLE] = std::make_unique<TitleScene>();
	sceneArr_[SCENE_ID_GAME] = std::make_unique<GameScene>();
	sceneArr_[SCENE_ID_CLEAR] = std::make_unique<ClearScene>();

	currentSceneNo_ = SCENE_ID_TITLE;
}

GameManager::~GameManager() {
}

int GameManager::Run() {

	// キー入力結果を受け取る箱
	std::vector<char> keys(256);
	std::vector<char> preKeys(256);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		preKeys = keys;
		Novice::GetHitKeyStateAll(keys.data());

		// シーン変更チェック
		int newSceneNo = IScene::GetSceneNo();
		if (newSceneNo != currentSceneNo_) {
			ChangeScene(newSceneNo);
			sceneArr_[currentSceneNo_]->Init();
		}

		///
		/// ↓更新処理ここから
		///

		sceneArr_[currentSceneNo_]->Update(keys, preKeys);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		sceneArr_[currentSceneNo_]->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}
	return 0;
}

void GameManager::ChangeScene(const int& newSceneNo) {
	if (newSceneNo >= 0 && newSceneNo < SCENE_ID_MAX) {
		prevSceneNo_ = currentSceneNo_;
		currentSceneNo_ = newSceneNo;
	}
}
