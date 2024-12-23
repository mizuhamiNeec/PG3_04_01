#pragma once
#include <base/WinApp.h>

#include "IScene.h"
#include "Vec2.h"

class GameScene final : public IScene {
public:
	void Init() override;
	void Update(std::vector<char>& keys, std::vector<char>& preKeys) override;
	void Draw() override;

private:
	// プレイヤー
	Vec2 playerPos_;
	float playerRadius_ = 0;
	float playerMoveSpeed_ = 0;
	bool isPlayerShooting_ = false;

	// プレイヤー弾
	Vec2 bulletPos_;
	float bulletRadius_ = 0;
	float bulletMoveSpeed_ = 0;

	// 敵
	Vec2 enemyPos_;
	float enemyRadius_ = 0;
	float enemyMoveSpeed_ = 0;
	int enemyRespawnTimer = 120;
	bool isEnemyAlive_ = true;
	bool isEnemyExplosion_ = false;

	// 爆発テクスチャ
	int ghExplode_ = -1;

	// 敵を倒した数
	int enemyKillCount_ = 0;
};

