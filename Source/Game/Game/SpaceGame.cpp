#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Renderer/Model.h"
#include "Player.h"
#include "Engine.h"
#include "Enemy.h"
#include "Core/Random.h"
#include "Renderer/Font.h"
#include "Core/time.h"
#include "GameData.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"
#include "Powerup.h"
#include "Core/StringHelper.h"

bool SpaceGame::initialize(){

	scene = std::make_unique<bonzai::Scene>(this);
	titleFont = std::make_shared<bonzai::Font>();
	titleFont->load("radiospacebitmap.ttf", 128.0f);

	uiFont = std::make_shared<bonzai::Font>();
	uiFont->load("radiospacebitmap.ttf", 32.0f);
    titleText = std::make_unique< bonzai::Text>(titleFont);
    scoreText = std::make_unique< bonzai::Text>(uiFont);
    livesText = std::make_unique< bonzai::Text>(uiFont);
    healthText = std::make_unique< bonzai::Text>(uiFont);

	
	
    std::vector<std::unique_ptr< bonzai::Actor>> actors;
    


    return true;
}

void SpaceGame::update(float deltaTime){
    switch (gameState) {

    case GameState::INITIALIZING:
        gameState = GameState::TITLE;
		break;
    case GameState::TITLE:
        if (bonzai::getEngine().getInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
            gameState = GameState::STARTING_GAME;
        }
		break;
    case GameState::STARTING_GAME:
        score = 0;
        lives = 3;
        
        gameState = GameState::STARTING_LEVEL;
		break;

    case GameState::STARTING_LEVEL:
    {
		scene->removeAllActors();
        std::shared_ptr<bonzai::Model> model = std::make_shared <bonzai::Model>(GameData::shipPoints, bonzai::vec3{ .5f,.5f,1 });
        bonzai::Transform transform{ { (float)bonzai::getEngine().getRenderer().getWidth() * 0.5f,
            (float)bonzai::getEngine().getRenderer().getHeight() * 0.5f}//position
            ,0,//rotation
            4 };//size
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        player->damping = 0.001f; // Set damping to a very low value for more responsive movement
        player->speed = 510.0f; // Set speed to a higher value for faster movement
        player->rotateSpeed = 180.0f; // Set rotation speed 
        player->tag = "Player"; // Set the name of the player actor
        player->name = "Player"; // Set the name of the player actor

        scene->addActor(std::move(player));
        gameState = GameState::PLAYING_GAME;
    }
        break;
    case GameState::PLAYING_GAME:
        enemySpawnTimer  -= deltaTime;
        if (enemySpawnTimer <= 0.0f) {
            enemySpawnTimer = 3;
            
			spawnEnemy();
        }
        powerupSpawnTimer  -= deltaTime;
        if (powerupSpawnTimer <= 0.0f) {
            powerupSpawnTimer = 15;
            
			spawnPowerup(powerups[bonzai::random::getInt(4)]);
        }
        


        break;
	case GameState::PLAYER_DEAD:
		stateTimer -= deltaTime;
        if (stateTimer > 0) {
            break;
        }
        lives--;
        if(lives <= 0) {
            gameState = GameState::GAME_OVER;
			stateTimer = 3.0f;
        } else {
            gameState = GameState::STARTING_LEVEL;
		}
        break;
    case GameState::GAME_OVER:
        stateTimer -= deltaTime;
        if(stateTimer > 0) {
            break;
		}
		gameState = GameState::TITLE;
        break;
    }

    if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_Q)) {
        bonzai::getEngine().getTime().setTimeScale(.2f);
    }else {
        bonzai::getEngine().getTime().setTimeScale(1.0f);
    }
    scene->update(bonzai::getEngine().getTime().getDeltaTime());

}

void SpaceGame::shutdown(){
}

void SpaceGame::draw( bonzai::Renderer& renderer){

    if (gameState == GameState::TITLE) {
        titleText->create(renderer, "SPACE GAME", bonzai::vec3{ 0,1,0 });
        titleText->draw(renderer, 20.0f, renderer.getHeight() * 0.5f);
    }
    if (gameState == GameState::GAME_OVER) {
		titleText->create(renderer, "GAME OVER", bonzai::vec3{ 1,0,0 });
		titleText->draw(renderer, 20.0f, renderer.getHeight() * 0.5f);
    }
	scoreText->create(renderer, "SCORE: " + std::to_string(score), bonzai::vec3{ 1,1,1 });
	scoreText->draw(renderer, 10.0f, 10.0f);

	livesText->create(renderer, "LIVES: " + std::to_string(lives), bonzai::vec3{ 1,1,1 });
	livesText->draw(renderer, (float)renderer.getWidth() - 200.0f, 10.0f);
    
    Player* player = dynamic_cast<Player*> (scene->getActorByName("Player"));
    if (player) {
        healthText->create(renderer, "HP: " + std::to_string(player->health), bonzai::vec3{ 1,0,0 });
        healthText->draw(renderer, (float)renderer.getWidth() - 200.0f, 60.0f);
    }

    scene->draw(renderer);

	bonzai::getEngine().getParticlesSystem().draw(renderer);

}

void SpaceGame::onDeath(){
	gameState = GameState::PLAYER_DEAD;
    stateTimer = 2;
}

void SpaceGame::spawnEnemy(){
	Player* player = scene->getActorByName<Player>("Player");
    if (player) {
        std::shared_ptr<bonzai::Model> enemyModel = std::make_shared <bonzai::Model>(GameData::enemyPoints,
            bonzai::vec3{ 1,0,1 });

		// Spawn enemy at a random position around the player, but not too close
        bonzai::vec2 position{ player->transform.position+bonzai::random::onUnitCircle() *bonzai::random::getReal(350.0f,650.0f)};

        bonzai::Transform transform{ position, bonzai::random::getReal(360.0f), 3};
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
        enemy->speed = 50.0f + bonzai::random::getReal(50.0f, 100.0f); // Random speed between 100 and 200
        enemy->shootCooldown = 2.0f + bonzai::random::getReal(0.0f, 2.0f); // Random shoot cooldown between 2 and 4 seconds
        enemy->damping = 0.0001f;
        enemy->tag = "Enemy";
        scene->addActor(std::move(enemy));
    }
}
void SpaceGame::spawnPowerup(std::string name){
	Player* player = scene->getActorByName<Player>("Player");
    if (player) {
        std::shared_ptr<bonzai::Model> powerupModel = nullptr;
        std::unique_ptr<Powerup> powerup = nullptr;

        if (bonzai::toLower(name) == "star") {
            powerupModel = std::make_shared <bonzai::Model>(GameData::starPowerupPoints,
                bonzai::vec3{ 1,1,0 });
        }else if(bonzai::toLower(name) == "health") {
            powerupModel = std::make_shared <bonzai::Model>(GameData::healthPowerupPoints,
                bonzai::vec3{ 0,1,0 });
        }else if(bonzai::toLower(name) == "tripleshot") {
            powerupModel = std::make_shared <bonzai::Model>(GameData::tripleShotPowerupPoints,
                bonzai::vec3{ 0,1,1 });
        }else if (bonzai::toLower(name) == "laser") {
            powerupModel = std::make_shared <bonzai::Model>(GameData::laserPowerupPoints,
                bonzai::vec3{ 0,1,1 });
        }
       
		// Spawn power at a random position around the player, but not too close
        bonzai::vec2 position{ player->transform.position+bonzai::random::onUnitCircle() *bonzai::random::getReal(200.0f,650.0f)};

        bonzai::Transform transform{ position, 0, 3};
         powerup = std::make_unique<Powerup>(transform, powerupModel);
    
        powerup->tag = "Powerup";
        powerup->name = name;
        powerup->lifespan = 7 + (float)bonzai::random::getInt(3);

        scene->addActor(std::move(powerup));
    }
}
