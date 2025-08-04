#include "InputSystem.h"
#include <SDL3/SDL.h>
namespace bonzai {
    bool InputSystem::initialize() {
		int numberOfKeys;
        const bool* keyboardState=SDL_GetKeyboardState(&numberOfKeys);

		this->keyboardState.resize(numberOfKeys);
		std::copy(keyboardState, keyboardState + numberOfKeys, this->keyboardState.begin());
        previousKeyboardState = this->keyboardState;

        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
        previousMousePosition = mousePosition;

        return true;
    }
    void InputSystem::shutdown() {
        //
    }
    void InputSystem::update(){
        //keybaord input
		previousKeyboardState = keyboardState;
        const bool* keyState = SDL_GetKeyboardState(nullptr);
        std::copy(keyState, keyState + keyboardState.size(), keyboardState.begin());
		//mouse input
        previousMousePosition = mousePosition;
		uint32_t mouseButtonState= SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
		previousMouseButtonState = this->mouseButtonState;
		this->mouseButtonState[(uint8_t)MouseButton::LEFT] = (mouseButtonState & SDL_BUTTON_LMASK);
		this->mouseButtonState[(uint8_t)MouseButton::MIDDLE] = (mouseButtonState & SDL_BUTTON_MMASK);
		this->mouseButtonState[(uint8_t)MouseButton::RIGHT] = (mouseButtonState & SDL_BUTTON_RMASK);

    }
}