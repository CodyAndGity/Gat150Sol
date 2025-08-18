#pragma once
#include "Core/StringHelper.h"
#include "Core/Singleton.h"
#include "Resource.h"
#include "Core/Logger.h"
#include <map>
#include <iostream>
namespace bonzai {
	class ResourceManager: public Singleton<ResourceManager> {
	public:
		void clear(){
			resources.clear();
		}

		template<typename T, typename ... Args>
			requires std::derived_from<T, Resource>

		res_t<T> get(const std::string& name, Args&& ... args);

		template<typename T, typename ... Args>
			requires std::derived_from<T, Resource>
		res_t<T> getWithID(const std::string& id, const std::string& name, Args&& ... args);

		
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
	private:
		std::map<std::string, res_t<Resource>> resources;
	};

	template<typename T, typename ... Args>
		requires std::derived_from<T, Resource>
	inline res_t<T> ResourceManager::get(const std::string& name, Args&& ... args) {
		return getWithID<T>(name, name, std::forward<Args>(args)...);

	}

	template<typename T, typename ...Args>
		requires std::derived_from<T, Resource>
	inline res_t<T> ResourceManager::getWithID(const std::string& id, const std::string& name, Args && ...args){
		// Convert name to lowercase for case-insensitive comparison
		std::string key = toLower(id);
		auto iter = resources.find(key);

		if (iter != resources.end()) {
			//get value in iterator
			auto base = iter->second;
			// Cast data to type T
			auto derived = std::dynamic_pointer_cast<T>(base);
			//check if cast was successful
			if (derived == nullptr) {
				Logger::Error("Resource type Mismatch: {} is not of type {}", key, typeid(T).name());
				
				return res_t<T>();
			}
			return derived;
		}
		//load resource
		res_t<T> resource = std::make_shared<T>();
		if (resource->load(name, std::forward<Args>(args)...) == false) {
			Logger::Error("Failed to load resource: {}", name);
			
			return res_t<T>();
		}
		//add resource to resource manager
		this->resources[key] = resource;
		return resource;

	}

	inline ResourceManager& resources() { return ResourceManager::getInstance(); }
}