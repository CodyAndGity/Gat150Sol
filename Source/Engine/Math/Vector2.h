#pragma once
#include "Math.h"
#include <cassert>
namespace bonzai {
	template<typename T>

	struct Vector2 {
		union {
			struct { T x, y; };
			struct { T u, v; };
		};
		
		Vector2() = default;
		Vector2(T x, T y) : x(x), y(y) {}

			
		T operator [] (unsigned int index) const {assert(index < 2);  return (&x)[index];}
		T& operator [] (unsigned int index) {assert(index < 2);  return (&x)[index];}

		Vector2 operator+(const Vector2& value) const { return Vector2{ x + value.x,y + value.y }; }
		Vector2 operator-(const Vector2& value) const { return Vector2{ x - value.x,y - value.y }; }
		Vector2 operator*(const Vector2& value) const { return Vector2{ x * value.x,y * value.y }; }
		Vector2 operator/(const Vector2& value) const { return Vector2{ x / value.x,y / value.y }; }

		Vector2 operator+(float value) const { return Vector2{ x + value,y + value }; }
		Vector2 operator-(float value) const { return Vector2{ x - value,y - value }; }
		Vector2 operator*(float value) const { return Vector2{ x * value,y * value }; }
		Vector2 operator/(float value) const { return Vector2{ x / value,y / value }; }

		Vector2& operator+=(const Vector2& value) { x += value.x; y += value.y; return *this; }
		Vector2& operator-=(const Vector2& value) { x -= value.x; y -= value.y; return *this; }
		Vector2& operator*=(const Vector2& value) { x *= value.x; y *= value.y; return *this; }
		Vector2& operator/=(const Vector2& value) { x /= value.x; y /= value.y; return *this; }

		Vector2& operator+=(float value) {  x += value; y += value; return *this ; }
		Vector2& operator-=(float value) {  x -= value; y -= value; return *this ; }
		Vector2& operator*=(float value) {  x *= value; y *= value; return *this ; }
		Vector2& operator/=(float value) { x /= value; y /= value; return *this ; }

		/// <summary>
		/// Calculates the squared length (magnitude) of a vector.
		/// </summary>
		/// <returns>The sum of the squares of the vector's x and y components.</returns>
		float lengthSquared()const { return x * x + y * y; }

		/// <summary>
		/// Calculates the length (magnitude) of a vector.
		/// </summary>
		/// <returns>The length of the vector as a floating-point value.</returns>
		float length() const { return math::sqrtf(lengthSquared()); }

		/// <summary>
		/// Returns a normalized (unit length) version of the vector.
		/// </summary>
		/// <returns>A vec2 representing the original vector scaled to have a length of 1.</returns>
		Vector2 normalized() const { return *this / length(); }

		/// <summary>
		/// Returns the angle, in radians, between the positive x-axis and the point (x, y).
		/// </summary>
		/// <returns>The angle in radians, computed using atan2f(y, x).</returns>
		float angle() const { return math::atan2f(y, x); }

		Vector2 rotate(float radians) const {
			Vector2 result;
			result.x = x * math::cosf(radians) - y * math::sinf(radians);
			result.y = x * math::sinf(radians) + y * math::cos(radians);

			return result;
		}

		/// <summary>
		/// Calculates the dot product of two 2D vectors.
		/// </summary>
		/// <param name="first">The first 2D vector.</param>
		/// <param name="second">The second 2D vector.</param>
		/// <returns>The dot product of the two vectors as a float.</returns>
		static float dot(const Vector2& first, const Vector2& second)  {
			return first.x * second.x + first.y * second.y;
		}

		/// <summary>
		/// Computes the 2D cross product (determinant) of two vectors.
		/// </summary>
		/// <param name="first">The first 2D vector.</param>
		/// <param name="second">The second 2D vector.</param>
		/// <returns>The scalar value representing the cross product of the two vectors.</returns>
		static float cross(const Vector2& first, const Vector2& second) {
			return first.x * second.y - first.y * second.x;
		}

		/// <summary>
		/// Calculates the angle between two 2D vectors.
		/// </summary>
		/// <param name="first">The first 2D vector.</param>
		/// <param name="second">The second 2D vector.</param>
		/// <returns>The angle between the two vectors, in radians.</returns>
		static float angleBetween(const Vector2& first, const Vector2& second) {
			return math::acosf(dot(first, second));
		}

		static float signedAngleBetween(const Vector2& first, const Vector2& second) {
			float x = dot(first, second);
			float y = cross(first, second);

			Vector2 result{ x,y };
			return result.angle();
		}
	};
	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}