#include "EventArgs.h"

namespace GameFramework {
	namespace IOModule {
		namespace Events {
			template <typename ArgType> void Event<ArgType>::operator() (void* sender, ArgType& arg) {
				arg.cancel = false;
				arg.timestamp = std::time(nullptr);
				for (auto i = funcs.begin(); i != funcs.end(); i++) {
					(*i)(sender, arg);
					if (arg.cancel) break;
				}
			}

			template<typename ArgType> inline unsigned Event<ArgType>::size(){
				return funcs.size();
			}

			template <typename ArgType> void Event<ArgType>::operator+=(std::function<void(void*, ArgType&)>& fun) {
				funcs.push_back(fun);
				funcs.unique();
			}

			template <typename ArgType> void Event<ArgType>::operator-=(std::function<void(void*, ArgType&)>& fun) {
				funcs.remove(fun);
			}
		}
	}
}