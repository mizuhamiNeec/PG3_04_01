#include <Novice.h>

#include "GameManager.h"

constexpr char kWindowTitle[] = "PG3_06_03_std::thread その2";

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>();

	gameManager->Run();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
