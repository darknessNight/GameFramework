#pragma once
#include "EventArgs.h"

namespace GF {
	namespace IOModule {
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
				arg.timestamp = std::time(nullptr);
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

			template<class ArgType>
			inline Delegate<ArgType>::Delegate(void(f)(ArgType &))
			{
				id = (int)f;
				func = std::function<void(ArgType&)>(f);
			}

			template<class ArgType>
			inline Delegate<ArgType>::Delegate(void(Object::* f)(ArgType &), Object * obj)
			{
				id = (int)obj;
				primaryFunc = f;
				func = std::bind(f, obj, std::placeholders::_1);
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
			inline bool Delegate<ArgType>::operator==(const Delegate & com)
			{
				return(this->id == com.id && this->primaryFunc == com.primaryFunc);
			}

			template<typename ArgType>
			inline void Delegate<ArgType>::operator()(ArgType &a)
			{
				func(a);
			}


		}
	}
}