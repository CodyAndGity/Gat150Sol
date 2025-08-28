#include "../GamePCH.h"

#include "PlatformerGame.h"

bool PlatformerGame::initialize() {
    OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);


    scene = std::make_unique<bonzai::Scene>(this);

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
        break;
    case PlatformerGame::GameState::PLAYER_DEAD:
        break;
    case PlatformerGame::GameState::GAME_OVER:
        break;
    default:
        break;
    }

    if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_Q)) {
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

    bonzai::getEngine().getParticlesSystem().draw(renderer);
}

void PlatformerGame::onDeath() {

}

// Inherited via IObserver
void PlatformerGame::onNotify(const bonzai::Event& event){

}

void PlatformerGame::spawnEnemy() {
    auto enemy = bonzai::Instantiate("PlatformEnemy");
    if (enemy) {
        scene->addActor(std::move(enemy));

    }

}
void PlatformerGame::spawnPlayer() {
    auto player = bonzai::Instantiate("PlatformPlayer");
    if (player) {
        scene->addActor(std::move(player));

    }
}
void PlatformerGame::spawnPowerup(std::string name) {

}