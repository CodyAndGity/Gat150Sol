#pragma once
#include "Core/Serializable.h"
#include <string>
#define CLASS_PROTOTYPE(className) virtual std::unique_ptr<Object> clone() {return std::make_unique<className>(*this);}

namespace bonzai {
	class Object : public ISerializable {
	public:
		std::string name;
		bool active{ true };
	public:
		Object() = default;
		virtual ~Object() = default;
		virtual std::unique_ptr<Object> clone() = 0;
		virtual void read(const json::value_t& value) override;

	};

}