#include "../GamePCH.h"
#include "SpaceGame.h"

#include "Player.h"
#include "Engine.h"
#include "Enemy.h"
#include "Components/SpriteRenderer.h"



#include "Powerup.h"


bool SpaceGame::initialize(){

	scene = std::make_unique<bonzai::Scene>(this);

	bonzai::json::document_t document;
    bonzai::json::load("scene.json", document);
    scene->read(document);
    titleText = std::make_unique< bonzai::Text>(bonzai::resources().getWithID<bonzai::Font>("title_font","radiospacebitmap.ttf", 128.0f));
    scoreText = std::make_unique< bonzai::Text>(bonzai::resources().getWithID<bonzai::Font>("ui_font", "radiospacebitmap.ttf", 32.0f));
    livesText = std::make_unique< bonzai::Text>(bonzai::resources().getWithID<bonzai::Font>("ui_font","radiospacebitmap.ttf", 32.0f));
    healthText = std::make_unique< bonzai::Text>(bonzai::resources().getWithID<bonzai::Font>("ui_font","radiospacebitmap.ttf", 32.0f));

	
	
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
        auto player = bonzai::Factory::getInstance().create<bonzai::Actor>("player");
        player->getComponent<bonzai::SpriteRenderer>()->setColor({ .8f,0.8f,1.0f });
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

    scene->draw(renderer);
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
    bonzai::Actor* player = scene->getActorByName<bonzai::Actor>("Player");
    
    
    if (player) {
        healthText->create(renderer, "HP: " + std::to_string(player->getComponent<Player>()->health), bonzai::vec3{ 1,0,0 });
        healthText->draw(renderer, (float)renderer.getWidth() - 200.0f, 60.0f);
    }


	bonzai::getEngine().getParticlesSystem().draw(renderer);

}

void SpaceGame::onDeath(){
	gameState = GameState::PLAYER_DEAD;
    stateTimer = 2;
}

void SpaceGame::spawnEnemy(){
    bonzai::Actor* player = scene->getActorByName<bonzai::Actor>("Player");
    if (player) {
        
        // Spawn enemy at a random position around the player, but not too close
        bonzai::vec2 position{ player->transform.position+bonzai::random::onUnitCircle() *bonzai::random::getReal(350.0f,650.0f)};
        
        //red_spaceship.png
		bonzai::Transform transform{ position, bonzai::random::getReal(360.0f), 3 };//3 for sprite size

        auto enemy = bonzai::Instantiate("Enemy", transform);
        enemy->getComponent<bonzai::SpriteRenderer>()->setColor({ 1.0f,0.5f,0.5f });

        scene->addActor(std::move(enemy));



    }
    /*
	
        enemy->speed = 50.0f + bonzai::random::getReal(50.0f, 100.0f); // Random speed between 100 and 200
        enemy->shootCooldown = 2.0f + bonzai::random::getReal(0.0f, 2.0f); // Random shoot cooldown between 2 and 4 seconds
    */

}
void SpaceGame::spawnPowerup(std::string name){
    bonzai::Actor* player = scene->getActorByName<bonzai::Actor>("Player");
    if (player) {

        // Spawn enemy at a random position around the player, but not too close
        bonzai::vec2 position{ player->transform.position + bonzai::random::onUnitCircle() * bonzai::random::getReal(350.0f,650.0f) };


        bonzai::Transform transform{ position, 0, 3 };//3 for sprite size
	    auto powerup = bonzai::Instantiate(name, transform);
        if (name == "laser") {
            powerup->getComponent<bonzai::SpriteRenderer>()->setColor({ 0.0f,1.0f,1.0f });
        }
        else {
            powerup->getComponent<bonzai::SpriteRenderer>()->setColor({ 1.0f,1.0f,1.0f });
        }
        scene->addActor(std::move(powerup));



    }
    

    /*
	
            
        

        }else if(bonzai::toLower(name) == "tripleshot") {
            spriteRenderer->textureName = "Textures/Triple_shot_powerup.png";
            spriteRenderer->setColor({ 1.0f,1.0f,1.0f });

            
            
        

       
		
        powerup->tag = "Powerup";
        powerup->name = name;
        powerup->lifespan = 7 + (float)bonzai::random::getInt(3);

        scene->addActor(std::move(powerup));
    }
    */
}
