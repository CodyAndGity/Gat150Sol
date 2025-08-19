#pragma once
#include "Json.h"
namespace bonzai {
	class Serializable {
	public:
		virtual ~Serializable() = default;
		virtual void read(const json::value_t& value) = 0;
	};
}