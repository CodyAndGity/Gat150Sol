#pragma once
#include "Core/Singleton.h"
#include "Event.h"
#include "Observer.h"
#include <map>
#include <list>
namespace bonzai {
	class EventManager : public Singleton<EventManager> {
	public:
		void addObserver(const Event::id_t& eventId, IObserver& observer);
		void removeObserver(IObserver& observer);

		void notify(const Event& event);
	
	private:
		std::map<Event::id_t, std::list<IObserver*>> observers;
	};
}