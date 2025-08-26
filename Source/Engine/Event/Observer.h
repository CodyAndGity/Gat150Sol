#pragma once
namespace bonzai {
	class IObserver {
	public:
		virtual ~IObserver();
		virtual void onNotify(const Event& event) = 0;
	};
}