#pragma once
#include "../stdafx.h"
#include <list>

namespace GF {
	namespace Core {
		class Object {};
		namespace Events {

			template<class ArgType> class Delegate {
			protected:
				std::function<void(ArgType&)> func;
				long long id;
				void(Object::*primaryFunc)(ArgType&) = nullptr;
			public:
				Delegate(void(f)(ArgType&));
				Delegate(void(Object::*f)(ArgType&), Object* obj);
				Delegate(std::function<void(ArgType&)>&);
				Delegate(std::function<void(ArgType&)>, long long id);
				Delegate(std::function<void(ArgType&)>, long long id, void(Object::*f)(ArgType&));
				Delegate(long long id);
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
			protected:
				std::list <Delegate<ArgType>> funcs;
			};

			struct EventArgs {
				void* sender;
				long long timestamp = 0;
				bool cancel = false;
			};
		}

		typedef Events::EventArgs EventArgs;
	}
}