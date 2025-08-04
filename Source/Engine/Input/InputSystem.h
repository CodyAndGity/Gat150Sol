#pragma once
#include "../Math/Vector2.h"
#include <vector>
#include <array>
namespace bonzai {
	class InputSystem {
	public:
		enum class MouseButton : uint8_t {
			LEFT,
			MIDDLE,
			RIGHT,
		};
	public:
		InputSystem() = default;
		bool initialize();
		void shutdown();

		void update();

		//keyboard input
		bool getKeyDown(uint8_t key) const { return keyboardState[key]; }
		bool getPreviousKeyDown ( uint8_t key) const { return previousKeyboardState[key];}
		bool getKeyPressed(uint8_t key) const { return !previousKeyboardState[key] && keyboardState[key]; }
		bool getKeyReleased(uint8_t key) const { return previousKeyboardState[key] && !keyboardState[key]; }

		const vec2& getMousePosition() const { return mousePosition; }
		const vec2& getPreviousMousePosition() const { return previousMousePosition; }

		//Mouse input
		bool getMouseButtonDown(MouseButton button) const {  return mouseButtonState[(uint8_t)button]; }
		bool getPreviousMouseButtonDown(MouseButton button) const {  return previousMouseButtonState[(uint8_t)button]; }
		bool getMouseButtonPressed(MouseButton button) const {  return mouseButtonState[(uint8_t)button] &&!previousMouseButtonState[(uint8_t)button]; }
		bool getMouseButtonReleased(MouseButton button) const {  return !mouseButtonState[(uint8_t)button] &&previousMouseButtonState[(uint8_t)button]; }
	private:
		std::vector<bool> keyboardState;
		std::vector<bool> previousKeyboardState;

		vec2 mousePosition{ 0,0 };
		vec2 previousMousePosition{ 0,0 };

		std::array<bool,3> mouseButtonState = { false, false, false };
		std::array<bool, 3> previousMouseButtonState = { false, false, false };
	};

}