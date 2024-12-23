#include "ClearScene.h"

#include "Novice.h"

void ClearScene::Init() {
}

void ClearScene::Update([[maybe_unused]] std::vector<char>& keys, [[maybe_unused]] std::vector<char>& preKeys) {
	// タイトルに戻る
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		sceneNo_ = SCENE_ID_TITLE;
	}
}

void ClearScene::Draw() {
	Novice::ScreenPrintf(16, 16, "Clear!!");
}