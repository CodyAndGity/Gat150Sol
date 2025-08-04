#pragma once
#include <chrono>
namespace bonzai {
	class Time {
	private:
		using clock =std::chrono::high_resolution_clock;
	public:
		Time() {
			startTime = clock::now();
			frameTime = clock::now();
		}
		void tick();
		void reset(){
			startTime = clock::now();
		}

		float getTime() const {
			return time;
		}
		float getDeltaTime() const {
			return deltaTime*timeScale;
		}
		void setTimeScale(float scale) {
			timeScale= scale ;
		}
	private:
		float time{ 0 };
		float deltaTime{ 0 };
		float timeScale{ 1 };
		clock::time_point startTime;
		clock::time_point frameTime;
	};

}