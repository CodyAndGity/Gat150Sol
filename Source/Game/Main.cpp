#include "EnginePCH.h"
#include "Core/Logger.h"
#include "Game/SpaceGame.h"
#include "Math/Vector2.h"
#include "Platformer/PlatformerGame.h"


int main(int argc, char* argv[]) {
	
    bonzai::file::SetCurrentDirectory("Assets/Platformer");
    

	bonzai::getEngine().initialize();
   
	
    //initialize game
	std::unique_ptr<bonzai::Game> game = std::make_unique<PlatformerGame>();
	game->initialize();
	
	
    SDL_Event e;
    bool quit = false;
	
    
	
   
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
       

		
		
		game->draw(bonzai::getEngine().getRenderer());
        
        bonzai::getEngine().getRenderer().present();
       
    }
	
    game->shutdown();
	game.release();
    bonzai::getEngine().shutdown();

    return 0;
}