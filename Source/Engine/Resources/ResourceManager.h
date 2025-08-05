#pragma once
#include "Core/StringHelper.h"
#include "Resource.h"
#include <map>
#include <iostream>
namespace bonzai {
	class ResourceManager {
	public:
		template<typename T, typename ... TArgs>
		res_t<T> get(const std::string& name, TArgs&& ... args);


		static inline ResourceManager& getResourceManager() {
			static ResourceManager instance;
			return instance;
		}
	private:
		ResourceManager() = default;
	private:
		std::map<std::string, res_t<Resource>> resources;
	};

	template<typename T, typename ... TArgs>
	inline res_t<T> ResourceManager::get(const std::string& name, TArgs&& ... args) {
		// Convert name to lowercase for case-insensitive comparison
		std::string key = toLower(name);
		auto iter =resources.find(key);
		if(iter != resources.end()) {
			//get value in iterator
			auto base = iter->second;
			// Cast data to type T
			auto derived=std::dynamic_pointer_cast<T>(base);
			//check if cast was successful
			if (derived==nullptr) {
				std::cerr << "Resource type Mismatch: " << key << " is not of type " << typeid(T).name() << std::endl;
				return res_t<T>();
			} 
			return derived;
		}
		//load resource
		res_t<T> resource = std::make_shared<T>();
		if(resource->load(key, std::forward<TArgs>(args)...)==false) {
			std::cerr << "Failed to load resource: " << key << std::endl;
			return res_t<T>();
		}
		//add resource to resource manager
		this->resources[key] = resource;
		return resource;

	}

	
}