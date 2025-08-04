#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>

namespace bonzai::math {
	
	constexpr float pi = 3.14159265358979323846f;
	constexpr float twoPi = 2.0f * pi;
	constexpr float halfPi = 0.5f * pi;
	/// <summary>
	/// Converts an angle from radians to degrees.
	/// </summary>
	/// <param name="radians">The angle in radians to convert.</param>
	/// <returns>The equivalent angle in degrees.</returns>
	constexpr float radToDeg(float radians) { return radians * (180.0f / pi); }
	/// <summary>
	/// Converts an angle from degrees to radians.
	/// </summary>
	/// <param name="degrees">The angle in degrees to convert.</param>
	/// <returns>The angle in radians.</returns>
	constexpr float degToRad(float degrees) { return degrees * (pi / 180.0f); }


	constexpr int wrap(int value, int min, int max) {
		int range = max - min;
		int result = (value - min) % range;
		if (result < 0) {
			result += range;
		}
		return result + min;
	}
	inline float wrap(float value, float min, float max) {
		float range = max - min;
		float result = std::fmod(value - min, range);
		if (result < 0) {
			result += range;
		}
		return result + min;
	}
	/// <summary>
	/// Determines the sign of a value.
	/// </summary>
	/// <typeparam name="T">The type of the value.</typeparam>
	/// <param name="value">The value whose sign is to be determined.</param>
	/// <returns>Returns 1 if the value is positive, -1 if negative, and 0 if zero.</returns>
	template<typename T>
	inline T sign(T value) {
		return (value<0) ? (T)-1 : (value>0) ?  (T)1 : (T)0;
	}

	//*pirate music plays*
	using std::min;
	using std::max;
	using std::clamp;
	using std::sqrt;
	using std::sqrtf;
	using std::sin;
	using std::sinf;
	using std::cos;
	using std::cosf;
	using std::acosf;
	using std::atan2;
	using std::atanf;
	using std::atan2f;
	using std::abs;
	using std::fabs;
	
}