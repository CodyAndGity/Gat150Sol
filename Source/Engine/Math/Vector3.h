#pragma once
#include "Math.h"
#include <cassert>
#include <iostream>
namespace bonzai {
	template<typename T>
	
	struct Vector3 {
		union {
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		
		Vector3() = default;
		Vector3(T x, T y,T z) : x(x), y(y), z(z) {}

			
		T operator [] (unsigned int index) const {assert(index < 3);  return (&x)[index];}
		T& operator [] (unsigned int index) {assert(index < 3);  return (&x)[index];}

		Vector3 operator+(const Vector3& value) const { return Vector3{ x + value.x,y + value.y,z + value.z };
		}
		Vector3 operator-(const Vector3& value) const { return Vector3{ x - value.x,y - value.y,z - value.z }; }
		Vector3 operator*(const Vector3& value) const { return Vector3{ x * value.x,y * value.y,z * value.z }; }
		Vector3 operator/(const Vector3& value) const { return Vector3{ x / value.x,y / value.y,z / value.z }; }

		Vector3 operator+(float value) const { return Vector3{ x + value,y + value,z + value }; }
		Vector3 operator-(float value) const { return Vector3{ x - value,y - value,z - value }; }
		Vector3 operator*(float value) const { return Vector3{ x * value,y * value,z * value }; }
		Vector3 operator/(float value) const { return Vector3{ x / value,y / value,z / value }; }

		Vector3& operator+=(const Vector3& value) { x += value.x; y += value.y;z += value.z; return *this; }
		Vector3& operator-=(const Vector3& value) { x -= value.x; y -= value.y;z -= value.z; return *this; }
		Vector3& operator*=(const Vector3& value) { x *= value.x; y *= value.y;z *= value.z; return *this; }
		Vector3& operator/=(const Vector3& value) { x /= value.x; y /= value.y;z /= value.z; return *this; }

		Vector3& operator+=(float value) {  x += value; y += value;z += value; return *this ; }
		Vector3& operator-=(float value) {  x -= value; y -= value;z -= value; return *this ; }
		Vector3& operator*=(float value) {  x *= value; y *= value;z *= value; return *this ; }
		Vector3& operator/=(float value) {  x /= value; y /= value;z /= value; return *this ; }

		/// <summary>
		/// Calculates the squared length of a 3D vector.
		/// </summary>
		/// <returns>The sum of the squares of the x, y, and z components.</returns>
		float lengthSquared() { return x * x + y * y + z*z; }

		/// <summary>
		/// Calculates the length (magnitude) of a vector.
		/// </summary>
		/// <returns>The length of the vector as a floating-point value.</returns>
		float length() { return math::sqrtf(lengthSquared()); }
	};

	template<typename T>
	std::ostream& operator << (std::ostream& stream, const Vector3<T>& vector) {
		stream << "{" << vector.x << ", " << vector.y << ", " << vector.z << "}";
		return stream;
	}

	template<typename T>
	std::istream& operator >> (std::istream& stream, Vector3<T>& vector) {
		char ch = '\0';
		if (!(stream >> std::ws >> ch) || ch != '{') {// read '{'
			stream.setstate(std::ios::failbit);
			return stream;
		}
		if (!(stream >> std::ws >> vector.x)) { // read x
			stream.setstate(std::ios::failbit);

			return stream;
		}
		if (!(stream >> std::ws >> ch) || ch != ',') {// read ','
			stream.setstate(std::ios::failbit);

			return stream;
		}
		if (!(stream >> std::ws >> vector.y)) { // read y
			stream.setstate(std::ios::failbit);

			return stream;
		}
		if (!(stream >> std::ws >> ch) || ch != ',') {// read ','
			stream.setstate(std::ios::failbit);

			return stream;
		}
		if (!(stream >> std::ws >> vector.z)) { // read y
			stream.setstate(std::ios::failbit);

			return stream;
		}
		if (!(stream >> std::ws >> ch) || ch != '}') {// read '}'
			stream.setstate(std::ios::failbit);

			return stream;
		}

		return stream;
	}
	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}