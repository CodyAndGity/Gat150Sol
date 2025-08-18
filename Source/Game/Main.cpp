#include "EnginePCH.h"
#include "Core/Logger.h"
#include "Game/SpaceGame.h"
#include "Math/Vector2.h"

class Animal {
public:
    virtual void speak() = 0;
};
class Cat : public Animal {
public:
    void speak() override {
        std::cout << "Meow" << std::endl;
	}
};
class Dog : public Animal {
public:
    void speak() override {
        std::cout << "Woof" << std::endl;
	}
    void fetch() {
        std::cout << "Fetching the ball!" << std::endl;
	}
};
class Bird : public Animal {
public:
    void speak() override {
        std::cout << "Chirp" << std::endl;
	}
};

enum class AnimalType {
    CAT = 1,
    DOG = 2,
    BIRD = 3
};
Animal* createAnimal(AnimalType id) {
	Animal* animal = nullptr;
    switch (id) {
    case AnimalType::CAT:
		animal= new Cat();
        break;
    case AnimalType::DOG:
		animal= new Dog();
        break;
    case AnimalType::BIRD:
		animal= new Bird();
        break;
    default:
        break;
    }
    return animal;
}


int main(int argc, char* argv[]) {

    bonzai::file::SetCurrentDirectory("Assets");
    // load the json data from a file
    auto animal = createAnimal(AnimalType::BIRD);
    if (animal) {
        animal->speak();
        auto dog = dynamic_cast<Dog*>(animal);
        if(dog){
			dog->fetch();
		}
        
    }
	
	//auto spriteRenderer = bonzai::Factory::getInstance().create("MeshRenderer");
    //spriteRenderer->name = "Steve";
   
    //return 0;
    // Initialize engine systems
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