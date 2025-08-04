



#include "Framework/Actor.h"
#include "Framework/Scene.h"

#include "Game/SpaceGame.h"
#include "Engine.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Core/Random.h"
#include "Core/File.h"

#include <iostream>
#include <vector>
#include <memory>





int main(int argc, char* argv[]) {

    bonzai::file::SetCurrentDirectory("Assets");
    // Initialize engine systems
	bonzai::getEngine().initialize();
   
    //initailize game
	std::unique_ptr<bonzai::Game> game = std::make_unique<SpaceGame>();
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