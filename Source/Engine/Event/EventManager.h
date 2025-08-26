#pragma once
#include "Core/Singleton.h"
#include "Event.h"
#include "Observer.h"
#include <map>
#include <list>

#define OBSERVER_ADD(event_id)				bonzai::EventManager::getInstance().addObserver(#event_id, *this)
#define OBSERVER_REMOVE_SELF				bonzai::EventManager::getInstance().removeObserver(*this)
#define EVENT_NOTIFY_DATA(event_id, data)	bonzai::EventManager::getInstance().notify({ #event_id, data })
#define EVENT_NOTIFY(event_id)				bonzai::EventManager::getInstance().notify({ #event_id, true })

namespace bonzai {
	class EventManager : public Singleton<EventManager> {
	public:
		void addObserver(const Event::id_t& eventId, IObserver& observer);
		void removeObserver(IObserver& observer);

		void notify(const Event& event);
		void removeAll() { observers.clear(); }
	private:
		std::map<Event::id_t, std::list<IObserver*>> observers;
	};
}