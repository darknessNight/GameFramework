#pragma once
#include "Events.h"
#include <time.h>

namespace GF {
	namespace Core {
		namespace Events {

			template<typename ArgType>
			inline void Event<ArgType>::operator+=(Delegate<ArgType> d)
			{
				funcs.push_back(d);
				funcs.unique();
			}

			template<typename ArgType>
			inline void Event<ArgType>::operator-=(Delegate<ArgType> d)
			{
				funcs.remove(d);
			}

			template <typename ArgType> inline void Event<ArgType>::operator() (void* sender, ArgType& arg) {
				arg.sender = sender;
				arg.cancel = false;
				arg.timestamp = time(nullptr);
				for (auto i = funcs.begin(); i != funcs.end(); i++) {
					(*i)(arg);
					if (arg.cancel) break;
				}
			}

			template<typename ArgType> inline unsigned Event<ArgType>::size() {
				return funcs.size();
			}

			template<typename ArgType> inline void Event<ArgType>::clear(){
				funcs.clear();
			}

			template<typename ArgType>
			inline bool Event<ArgType>::operator==(const Event<ArgType>& com)const
			{
				return com.funcs == funcs;
			}

			template<class ArgType>
			inline Delegate<ArgType>::Delegate(void(f)(ArgType &))
			{
				id = (long long)f;
				func = std::function<void(ArgType&)>(f);
			}

			template<class ArgType>
			inline Delegate<ArgType>::Delegate(void(Object::* f)(ArgType &), Object * obj)
			{
				id = (long long)obj;
				primaryFunc = f;
				func = std::bind(f, obj, std::placeholders::_1);
			}

			template<class ArgType>
			inline Delegate<ArgType>::Delegate(std::function<void(ArgType&)>& f)
			{
				func = f;
				id = (long long)&f;
			}

			template<class ArgType>
			inline Delegate<ArgType>::Delegate(std::function<void(ArgType&)> f, int id)
			{
				func = f;
				this->id = id;
			}

			template<class ArgType>
			inline Delegate<ArgType>::Delegate(std::function<void(ArgType&)>f, int id, void(Object::* pf)(ArgType &))
			{
				this->id = id;
				primaryFunc = pf;
				func = f;
			}

			template<class ArgType>
			inline Delegate<ArgType>::Delegate(int id)
			{
				this->id = id;
			}

			template<class ArgType>
			inline Delegate<ArgType>::Delegate(int id, void(Object::*f)(ArgType&))
			{
				this->id = id;
				primaryFunc = f;
			}

			template<typename ArgType>
			inline void Delegate<ArgType>::operator()(ArgType &a)
			{
				func(a);
			}

			template<typename ArgType> bool Delegate<ArgType>::operator==(const Delegate<ArgType>& rhs) const {
				return id == rhs.id&&primaryFunc == rhs.primaryFunc;
			}
		}
	}
}