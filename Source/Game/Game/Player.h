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
	Player(const bonzai::Transform& transform, bonzai::res_t<bonzai::Texture> texture) :
		bonzai::Actor{ transform, texture }
	{}

	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(Actor* other) override;



private:
	bonzai::vec3 starColors[3]{ texture->color,{100,100,0},{10,0,0}};
	int starColorIndex{ 0 };
	float powerupTimer{ 0.0f };


};