#pragma once
#include "Framework/Actor.h"
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

	template<typename T>
		requires std::derived_from<T, Object>
	class PrototypeCreator :public CreatorBase {
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) : prototype(std::move(prototype)) {
			if (!this->prototype) {
				Logger::Error("PrototypeCreator: Prototype is null");
			}
		}
		std::unique_ptr<Object> Create() override {
			return prototype->clone();
		}
	private:
		std::unique_ptr<T> prototype;
	};

	class Factory : public Singleton<Factory>{
	public:
		template<typename T>
		requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template<typename T>
		requires std::derived_from<T, Object>
		void RegisterPrototype(const std::string& name,std::unique_ptr<T> prototype);

		template<typename T=Object>
		requires std::derived_from<T, Object>
		std::unique_ptr<T> create(const std::string& name);
		void removeAll() { registry.clear(); }
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
	inline void Factory::RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype)	{
		//make case insensitive
		std::string key = toLower(name);
		//add prototype creator to registry
		registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
		Logger::Info("{} prototype added to factory", name);
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
			auto object = iter->second->Create();
			T* derived = dynamic_cast<T*>(object.get());
			if(derived) {
				object.release(); // Transfer ownership to the caller
				return std::unique_ptr<T>(derived);
			}
			Logger::Error("Factory: Type mismatch of class/Object with name: {}", name);

		}
		else {
			Logger::Error("Factory: No class/Object registered with name: {}", name);
		}
		return nullptr; 
	}
	template<typename T = Actor>
		requires std::derived_from<T, Actor>
	inline std::unique_ptr<T> Instantiate(const std::string& name) {
		return Factory::getInstance().create<T>(name);
	}

	template<typename T = Actor>
		requires std::derived_from<T, Actor>
	inline std::unique_ptr<T> Instantiate(const std::string& name, const vec2& position, float rotation, float scale) {
		auto instance = Factory::getInstance().create<T>(name);
		instance->transform = Transform{ position, rotation, scale };
		return instance;
	}

	template<typename T = Actor>
		requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name, const Transform& transform) {
		auto instance = Factory::getInstance().create<T>(name);
		instance->transform = transform;
		return instance;
	}
}