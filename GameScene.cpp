#include "GameScene.h"

#include <fstream>
#include <mutex>
#include <sstream>

#include "Novice.h"

void GameScene::Init() {
	loadThread_ = std::thread(&GameScene::LoadCSV, this);
}

void GameScene::Update([[maybe_unused]] std::vector<char>& keys, [[maybe_unused]] std::vector<char>& preKeys) {
}

void GameScene::Draw() {
	Novice::ScreenPrintf(32, 512, "CSV loaded = %d", csvLoaded_);

	if (csvLoaded_) {
		std::lock_guard lock(mapDataMutex_);
		const int tileSize = 12;
		for (size_t i = 0; i < mapData_.size(); ++i) {
			for (size_t j = 0; j < mapData_[i].size(); ++j) {
				int tile = mapData_[i][j];
				if (tile == 0) {
					continue;
				}

				Novice::DrawBox(
					static_cast<int>(j) * tileSize, static_cast<int>(i) * tileSize,
					tileSize, tileSize,
					0.0f,
					0xFFFFFFFF,
					kFillModeSolid
				);
			}
		}
	}
}

GameScene::~GameScene() {
	if (loadThread_.joinable()) {
		loadThread_.join();
	}
}

void GameScene::LoadCSV() {
	std::ifstream file("map.csv");
	if (!file.is_open()) {
		return;
	}

	std::vector<std::vector<int>> data;
	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> row;
		std::istringstream ss(line);
		std::string token;
		while (std::getline(ss, token, ',')) {
			try {
				row.push_back(std::stoi(token));
			} catch (...) {
				row.push_back(0);
			}
		}
		data.push_back(row);
	}
	file.close();

	{
		std::lock_guard lock(mapDataMutex_);
		mapData_ = data;
		csvLoaded_ = true;
	}
}
