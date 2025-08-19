#include "EnginePCH.h"
#include "Transform.h"
#include "Core/Json.h"
namespace bonzai{
	void Transform::read(const json::value_t& value) {
		JSON_READ(value, position);
		JSON_READ(value, rotation);
		JSON_READ(value, scale);
	}

}