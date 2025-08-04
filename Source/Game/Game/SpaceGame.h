#pragma once
#include "../../Engine/Framework/Game.h"
#include "renderer/Font.h"
#include "renderer/Text.h"
#include <string>
#include <memory>
class SpaceGame :  public bonzai::Game {
public:
	enum class GameState {
		INITIALIZING,
		TITLE,
		STARTING_GAME,
		STARTING_LEVEL,
		PLAYING_GAME,
		PLAYER_DEAD,
		GAME_OVER

	};
public:
	SpaceGame() = default;

	// Inherited via Game
	bool initialize() override;

	void update(float deltaTime) override;

	void shutdown() override;

	void draw(class bonzai::Renderer& renderer) override;

	void onDeath();
private:

	void spawnEnemy();
	void spawnPowerup(std::string name);
private:

	GameState gameState = GameState::INITIALIZING;
	float enemySpawnTimer{ 0.0f };
	float powerupSpawnTimer{ 0.0f };
	float stateTimer{ 0.0f };
	std::string powerups[4] { "star","health","tripleShot","laser"};

	std::shared_ptr<class bonzai::Font> titleFont{ nullptr };
	std::shared_ptr<class bonzai::Font> uiFont{ nullptr };

	std::unique_ptr<class bonzai::Text> titleText{ nullptr };
	std::unique_ptr<class bonzai::Text> scoreText{ nullptr };
	std::unique_ptr<class bonzai::Text> livesText{ nullptr };
	std::unique_ptr<class bonzai::Text> healthText{ nullptr };
};