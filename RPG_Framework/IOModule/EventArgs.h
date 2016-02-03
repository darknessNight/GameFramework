#pragma once
#include <functional>
#include <list>

namespace RPGFramework {
	namespace IOModule {
		namespace Events {
			template<typename ArgType> class Event{
			public:
				void operator+=(std::function<void(void*, ArgType&)>&);
				void operator-=(std::function<void(void*, ArgType&)>&);
				void operator()(void*,ArgType&);
			private:
				std::list < std::function<void(void*, ArgType&)>> funcs;
			};

			struct EventArgs {
				int timestamp;
				bool cancel;
			};

			struct KeyboardArgs: EventArgs {
				short int Key;
			};

			struct MouseArgs: EventArgs {

			};
		}
	}
}