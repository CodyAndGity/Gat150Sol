#pragma once
#include "Framework/Component.h"
#include "Math/Vector3.h"
#include "Renderer/Texture.h"
#include "Core/Json.h"
class PlayerController : public bonzai::Component, public bonzai::ICollidable {
public:
	float speed{ 0 };
	float maxSpeed{ 0 };
	float shootCooldown{ 0.2f }; // seconds between shots
	float shootTimer{ 0.0f }; // timer to track shooting cooldown
	float jump{ 0.0f };
	bool starPowerActive{ false };
	bool tripleShotPowerActive{ false };
	bool laserPowerActive{ false };
	bool healthPowerActive{ false };
	int health{ 10 };
	

	bonzai::RigidBody* body{ nullptr };
public:
	PlayerController() = default;
	CLASS_PROTOTYPE(PlayerController)

		void start() override;
	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(class bonzai::Actor* other) override;

	inline void setBaseColor(bonzai::vec3 color) {
		starColors[0] = color;
	}
	void read(const bonzai::json::value_t& value) override;

	void shoot(float angle=0, std::string type="PlatformerRocket");
private:
	bonzai::vec3 starColors[3]{ { 0.8f,0.8f,1.0f },{100,100,0},{10,0,0} };
	int starColorIndex{ 0 };
	float powerupTimer{ 0.0f };
private:
	//void shoot(float angle = 0.0f, std::string type = "Rocket");

};