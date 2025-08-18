#pragma once
#include "Core/Singleton.h"
#include "Framework/Object.h"
#include "Core/StringHelper.h"
#include "Core/Logger.h"
#include <map>
#include <memory>
#include <string>

#define FACTORY_REGISTER(className)\
class Register##className {         \
public:                              \
        Register##className() {       \
            bonzai::Factory::getInstance().Register<className>(#className); \
		}                               \
};                                       \
Register##className registerInstance;     
namespace bonzai {
	class CreatorBase {
	public:
		virtual ~CreatorBase() = default;
		virtual std::unique_ptr<Object> Create() = 0;
	};

	template<typename T>
	requires std::derived_from<T, Object>
	class Creator:public CreatorBase{
	public:
		std::unique_ptr<Object> Create() override{
			return std::make_unique<T>();
		}
	};
	class Factory : public Singleton<Factory>{
	public:
		template<typename T>
		requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template<typename T=Object>
		requires std::derived_from<T, Object>
		std::unique_ptr<T> create(const std::string& name);

	private:
		std::map<std::string, std::unique_ptr<CreatorBase> > registry;
	};

	template<typename T>
	requires std::derived_from<T, Object>
	inline void Factory::Register(const std::string& name)	{
		//make case insensitive
		std::string key = toLower(name);
		//add creator to registry
		registry[key] = std::make_unique<Creator<T>>();
		Logger::Info("{} added to factory", name);

	}

	template<typename T>
	requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::create(const std::string& name){
		//make case insensitive
		std::string key = toLower(name);
		//look for creator in registry
		auto iter = registry.find(key);
		if (iter != registry.end()) {
			//found creator, create instance
			return iter->second->Create();
		}
		Logger::Error("Factory: No class/Object registered with name: {}", name);
		return nullptr;
	}
}