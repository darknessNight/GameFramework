#pragma once
#include "../stdafx.h"
#include "Types.h"
#include <list>

namespace GF {
	namespace Core {
		namespace Events {

			template<class ArgType> class Delegate {
			private:
				std::function<void(ArgType&)> func;
				int id;
				void(Object::*primaryFunc)(ArgType&)=nullptr;
			public:
				Delegate(void(f)(ArgType&));
				Delegate(void(Object::*f)(ArgType&),Object* obj);
				Delegate(std::function<void(ArgType&)>, int id);
				Delegate(std::function<void(ArgType&)> , int id, void(Object::*f)(ArgType&));
				Delegate(int id);
				Delegate(int id, void(Object::*)(ArgType&));
				bool operator==(const Delegate<ArgType>& rhs)const;
				void operator()(ArgType&);
			};

			template<typename ArgType> class Event {
			public:
				void operator+=(Delegate<ArgType>);
				void operator-=(Delegate<ArgType>);
				void operator()(void*, ArgType&);
				unsigned size();
				void clear();
				bool operator==(const Event<ArgType>& com)const;
			private:
				std::list <Delegate<ArgType>> funcs;
			};

			struct EventArgs {
				void* sender;
				int timestamp=0;
				bool cancel=false;
			};

		}
	}
}