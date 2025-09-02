#pragma once
#include <rapidjson/document.h>
#include <string>
#include <vector>
#include "Math/Vector2.h"
#include "Math/Vector3.h"

#define JSON_READ(value, data) bonzai::json::read(value, #data, data)
#define JSON_READ_NAME(value,name, data) bonzai::json::read(value, name, data)

#define JSON_HAS(value,data) value.HasMember(#data)
#define JSON_GET(value,data) value[#data]

namespace bonzai::json{
	using value_t = rapidjson::Value;
	using document_t= rapidjson::Document;

	bool load(const std::string& filename, document_t& document);

	bool read(const value_t& value, const std::string& name, int& data, bool required =false);
	bool read(const value_t& value, const std::string& name, float& data, bool required =false);
	bool read(const value_t& value, const std::string& name, bool& data, bool required =false);
	bool read(const value_t& value, const std::string& name, std::string& data, bool required =false);
	bool read(const value_t& value, const std::string& name, vec2& data, bool required =false);
	bool read(const value_t& value, const std::string& name, vec3& data, bool required =false);
	bool read(const value_t& value, const std::string& name, std::vector<int>& data, bool required =false);
}