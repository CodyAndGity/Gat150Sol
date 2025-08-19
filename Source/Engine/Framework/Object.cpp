#include "Object.h"
#include "EnginePCH.h"

#include "Core/Json.h"
namespace bonzai {
	void Object::read(const json::value_t& value) {
		JSON_READ(value, name);
		JSON_READ(value, active);

	}

}