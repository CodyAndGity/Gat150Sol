#include "EnginePCH.h"
#include "Core/Logger.h"
#include "Game/SpaceGame.h"
#include "Math/Vector2.h"

class A {
public:
    A() = default;
    A(int size) : size{ size } {
        buffer = new int[size];
        for (int i = 0; i < size; i++) {
            buffer[i] = i;
		}
    }
    A(const A& other) : 
        size{ other.size }  {
		 buffer = new int[other.size];
          for (int i = 0; i < size; i++) {
            buffer[i] = i;
        }
        } //{}//= default;// 
	A& operator=(const A& other){
        size = other.size+1;
        buffer = other.buffer;
        return *this; } //= default;// 
    ~A() = default;

public:
    int size{ 0 };
    int* buffer{ nullptr };
};

int main(int argc, char* argv[]) {
	A a1{ 4 };
	std::cout << "Size of a1: " << a1.size << std::endl;
	std::cout << " a1 buf: " << a1.buffer[2] << std::endl;

    A a2{ a1 };//copy constructor

    a1.buffer[2] = 45;
	std::cout << "Size of a2: " << a2.size << std::endl;
	std::cout << " a2 buf: " << a1.buffer[2] << std::endl;

    A a3;
    a3 = a1;//assignment operator
	std::cout << "Size of a3: " << a3.size << std::endl;


    return 0;
    bonzai::file::SetCurrentDirectory("Assets");
    

	bonzai::getEngine().initialize();
   
	
    //initialize game
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