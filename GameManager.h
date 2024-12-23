#pragma once
#include <memory>

#include "IScene.h"


class GameManager {
public:
	GameManager();
	~GameManager();

	int Run(); // この関数でゲームループを呼び出す

	void ChangeScene(const int& newSceneNo); // シーン変更
private:
	std::vector<std::unique_ptr<IScene>> sceneArr_;

	int currentSceneNo_ = SCENE_ID_NONE; // 現在のシーン
	int prevSceneNo_ = SCENE_ID_NONE; // 前のシーン
};

