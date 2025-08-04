#pragma once
#include <memory>

namespace bonzai {

	class Game {
	public:
		Game() = default;

		virtual bool initialize()=0;
		virtual void update( float deltaTime)=0;
		virtual void shutdown()=0;
		virtual void draw(class Renderer& renderer) = 0;
		void addScore(int score) { this->score += score; }
		int getScore() const { return score; }
		int getLives() const { return lives; }
		void setLives(int lives) { this->lives = lives; }
	protected:
		int score{ 0 };
		int lives{ 3 };
		std::unique_ptr<class Scene> scene;
	};
}