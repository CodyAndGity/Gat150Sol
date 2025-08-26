#include "Observer.h"
namespace bonzai {
	IObserver::~IObserver() {
		OBSERVER_REMOVE_SELF;
	}
}