#include "EnginePCH.h"
#include "Core/Logger.h"
#include "Game/SpaceGame.h"
#include "Math/Vector2.h"



int main(int argc, char* argv[]) {

    bonzai::file::SetCurrentDirectory("Assets");
    

	bonzai::getEngine().initialize();
   
	
    //initialize game
	std::unique_ptr<bonzai::Game> game = std::make_unique<SpaceGame>();
	game->initialize();
	
	bonzai::getEngine().getAudio().addSound("bass.wav", "bass.wav");
    SDL_Event e;
    bool quit = false;
	float rotateAngle = 0.0f;
    
	
   
	//Main loop
    while (!quit) {
		
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        //update engine systems
        bonzai::getEngine().update();
        //update game
        game->update(bonzai::getEngine().getTime().getDeltaTime());
        
        if(bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_ESCAPE)) {
            quit = true;
		}

        //draw
        bonzai::vec3 color{0,0,0};
        bonzai::getEngine().getRenderer().setColor(color.r,color.g,color.b);
        bonzai::getEngine().getRenderer().clear();
       

		rotateAngle += 90* bonzai::getEngine().getTime().getDeltaTime();
		
		game->draw(bonzai::getEngine().getRenderer());
        
        bonzai::getEngine().getRenderer().present();
       
    }
	
    game->shutdown();
	game.release();
    bonzai::getEngine().shutdown();

    return 0;
}