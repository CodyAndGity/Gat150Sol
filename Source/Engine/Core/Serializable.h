#pragma once
#include "Json.h"
namespace bonzai {
	class ISerializable {
	public:
		virtual ~ISerializable() = default;
		virtual void read(const json::value_t& value) = 0;
	};
}