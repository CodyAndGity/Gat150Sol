#pragma once
#include "../../Engine/Framework/Actor.h"
#include "Math/Vector3.h"
#include "Renderer/Texture.h"
class Player : public bonzai::Actor {
public:
	float speed{ 0 };
	float rotateSpeed{ 0 };
	float shootCooldown{ 0.2f }; // seconds between shots
	float shootTimer{ 0.0f }; // timer to track shooting cooldown
	bool starPowerActive{ false };
	bool tripleShotPowerActive{ false };
	bool laserPowerActive{ false };
	bool healthPowerActive{ false };
	int health{ 10 };
public:
	Player() = default;
	Player(const bonzai::Transform& transform) :
		bonzai::Actor{ transform }
	{}

	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(Actor* other) override;

	inline void setBaseColor(bonzai::vec3 color) {
		starColors[0] = color;
	}

private:
	bonzai::vec3 starColors[3]{ { 0.8f,0.8f,1.0f },{100,100,0},{10,0,0}};
	int starColorIndex{ 0 };
	float powerupTimer{ 0.0f };


};