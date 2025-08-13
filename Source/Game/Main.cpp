#include "EnginePCH.h"
#include "Core/Logger.h"
#include "Game/SpaceGame.h"
#include "Math/Vector2.h"

int main(int argc, char* argv[]) {

    bonzai::file::SetCurrentDirectory("Assets");

    //command -line arguments
	std::cout << argc << std::endl;
    for (int i = 0; i < argc; i++) {
		//bonzai::Logger::Debug("Arg {}: {}", i, argv[i]);
        
    }
    //streams
	//console input/output
	/*std::cout << "hi" << std::endl;
    int age{ 0 };
	std::cout << "Enter your age: ";
    if (!(std::cin >> age)) {
		std::cerr << "Invalid input. Please enter a number." << std::endl;
    }
	std::cout << "You are " << (age *365)<< " days old!" << std::endl;*/

    //file streams
    std::ifstream stream("text.txt");
    if (!stream) {
		std::cout << "Failed to open file." << std::endl;
    }
    std::cout << stream.rdbuf();

    std::string line;
    while (std::getline(stream, line)) {

		std::cout << line << std::endl;
    }
    //user data type streams


    bonzai::vec3 v={ 1.0f,2.2f,2.8f };
	std::cout << "Vector: " << v << std::endl;

	std::string vectorString("{23.4,45.6}");
	std::stringstream streamVec(vectorString);
	bonzai::vec2 v2;
	streamVec >> v2;
	std::cout << "Parsed Vector2: " << v2 << std::endl;

    return 0;
    // Initialize engine systems
	bonzai::getEngine().initialize();
   
	
    //initailize game
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