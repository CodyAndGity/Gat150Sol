#include "../GamePCH.h"

#include "PlatformerGame.h"

bool PlatformerGame::initialize() {
    OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);


    scene = std::make_unique<bonzai::Scene>(this);
    scoreText = std::make_unique< bonzai::Text>(bonzai::resources().getWithID<bonzai::Font>("ui_font", "radiospacebitmap.ttf", 32.0f));

    scene->load("scenes/prototypes.json");
    scene->load("scenes/level.json");
	return true;
}

void PlatformerGame::update(float deltaTime) {
    switch (gameState)
    {
    case PlatformerGame::GameState::INITIALIZING:
        gameState = GameState::STARTING_LEVEL;
        break;
    case PlatformerGame::GameState::TITLE:
        break;
    case PlatformerGame::GameState::STARTING_GAME:
        break;
    case PlatformerGame::GameState::STARTING_LEVEL:
        spawnPlayer();
        spawnEnemy();
        gameState = GameState::PLAYING_GAME;

        break;
    case PlatformerGame::GameState::PLAYING_GAME:
        enemySpawnTimer -= deltaTime;
        if (enemySpawnTimer <= 0.0f) {
            enemySpawnTimer = enemySpawnTimeReset;
            int enemyCount = 0;
            for(auto enemy : scene->getActorByTag("Enemy")) {
                if (enemy && !enemy->destroyed && enemy->active) {
                    enemyCount++;
                }
			}
            
            if (enemyCount < 20) {
                spawnEnemy();

                if (enemySpawnTimeReset > 0.5f) {
                    enemySpawnTimeReset -= 0.2f;//faster spawns over time
                }
            }
        }
        powerupSpawnTimer -= deltaTime;
        if (powerupSpawnTimer <= 0.0f) {
            powerupSpawnTimer = 15;

            spawnPowerup(powerups[bonzai::random::getInt(4)]);
        }
        break;
    case PlatformerGame::GameState::PLAYER_DEAD:
        break;
    case PlatformerGame::GameState::GAME_OVER:
        break;
    default:
        break;
    }

    if (bonzai::getEngine().getInput().getKeyPressed(SDL_SCANCODE_Q)) {
        spawnPowerup(powerups[bonzai::random::getInt(4)]);

        bonzai::getEngine().getTime().setTimeScale(.2f);
        
    }
    else {
        bonzai::getEngine().getTime().setTimeScale(1.0f);
    }

    scene->update(bonzai::getEngine().getTime().getDeltaTime());

}

void PlatformerGame::shutdown(){
    //
}

void PlatformerGame::draw(class bonzai::Renderer& renderer){
    scene->draw(renderer);
    scoreText->create(renderer, "SCORE: " + std::to_string(score), bonzai::vec3{ 0,0,0 });
    scoreText->draw(renderer, 10.0f, 10.0f);

    bonzai::getEngine().getParticlesSystem().draw(renderer);
}

void PlatformerGame::onDeath() {

}

// Inherited via IObserver
void PlatformerGame::onNotify(const bonzai::Event& event){
    if (bonzai::equalsIgnoreCase(event.id, "add_points")) {
        addScore(std::get<int>(event.data));
    }
}

void PlatformerGame::spawnEnemy() {
    
    /*bonzai::vec2 position = bonzai::vec2{ bonzai::random::getReal()*600+200,bonzai::random::getBool() ? 300.0f : 600.0f};
	auto transform = bonzai::Transform{ position,0.0f,1.0f };
    auto enemy = bonzai::Instantiate("PlatformEnemy");*/
    bonzai::Actor* player = scene->getActorByName<bonzai::Actor>("PlatformPlayer");
    if (player) {
        bonzai::vec2 position{ player->transform.position + bonzai::random::onUnitCircle() * bonzai::random::getReal(450.0f,750.0f) };

        auto transform = bonzai::Transform{ position,0.0f,1.5f };
        auto enemy = bonzai::Instantiate("bat",transform);
        if (enemy) {
            scene->addActor(std::move(enemy));

        }
    }

}
void PlatformerGame::spawnPlayer() {
    auto player = bonzai::Instantiate("PlatformPlayer");
    if (player) {
        scene->addActor(std::move(player));

    }
}
void PlatformerGame::spawnPowerup(std::string name) {
    bonzai::Actor* player = scene->getActorByName<bonzai::Actor>("PlatformPlayer");
    if (player) {

        // Spawn powerup at a random position around the player, but not too close
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
}