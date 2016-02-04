#pragma once
#include "EventArgs.h"

namespace GameFramework {
	namespace IOModule {
		namespace Events {
			template <typename ArgType> inline void Event<ArgType>::operator() (void* sender, ArgType& arg) {
				arg.cancel = false;
				arg.timestamp = std::time(nullptr);
				for (auto i = funcs.begin(); i != funcs.end(); i++) {
					(i->func)(sender, arg);
					if (arg.cancel) break;
				}
			}

			template<typename ArgType> inline unsigned Event<ArgType>::size() {
				return funcs.size();
			}

			template<typename ArgType> inline void Event<ArgType>::clear(){
				funcs.clear();
			}

			template <typename ArgType> inline int Event<ArgType>::operator+=(std::function<void(void*, ArgType&)> fun) {
				funcs.push_back(fun);
				funcs.unique();
				return lastId-1;
			}

			template <typename ArgType> inline void Event<ArgType>::operator-=(int del) {
				funcs.remove(del);
			}
		}
	}
}