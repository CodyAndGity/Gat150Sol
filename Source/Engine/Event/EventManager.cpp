#include "EnginePCH.h"
#include "Core/StringHelper.h"
namespace bonzai {
	void bonzai::EventManager::addObserver(const Event::id_t& eventId, IObserver& observer){
		observers[toLower(eventId)].push_back(&observer);
	}

	void bonzai::EventManager::removeObserver(IObserver& observer){
		IObserver* observerPointer = &observer;
		//iterate through all event types
		for (auto& eventType : observers) {
			//get list of observer for event type
			auto observers =eventType.second;
			//remove macthing observers from this event type
			std::erase_if(observers, [observerPointer](auto& observer) {
				return (observer == observerPointer);
			});
		}
	}

	void bonzai::EventManager::notify(const Event& event){
	}
}