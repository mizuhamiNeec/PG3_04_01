#include "TitleScene.h"

#include "Novice.h"

void TitleScene::Init() {
}

void TitleScene::Update([[maybe_unused]] std::vector<char>& keys, [[maybe_unused]] std::vector<char>& preKeys) {
	// スペースキーが押されたらゲームシーンに遷移
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		sceneNo_ = SCENE_ID_GAME;
	}
}

void TitleScene::Draw() {
	Novice::ScreenPrintf(16, 16, "Space To Start...");
}
