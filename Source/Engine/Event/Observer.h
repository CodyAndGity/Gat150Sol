#pragma once
namespace bonzai {
	class IObserver {
		virtual ~IObserver() = default;
		virtual void onNotify(const Event& event) = 0;
	};
}