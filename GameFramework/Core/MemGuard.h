#pragma once
#ifdef DEBUG
#include "../MemGuard.h"
#endif
#include <mutex>

namespace GF {
	namespace Core {

		template <typename T> class shared_ptr {
		protected:
			int* copies = nullptr;
			T* val = nullptr;
			std::mutex thsafe;
			std::mutex* userMutex=nullptr;
			std::thread::id uMutexId;
		protected:
			void init();
		public:
			bool deleting = false;

			shared_ptr() = default;
			//shared_ptr(T* val);//if don't know what is problem comment this line. It may solve problem
			shared_ptr(T& val);
			shared_ptr(shared_ptr<T> &&) = default;
			shared_ptr<T>& operator=(shared_ptr<T> &&) = default;

			shared_ptr(const shared_ptr<T>& ref);
			shared_ptr(std::nullptr_t);
			~shared_ptr();
			void lockPtr();
			void unlockPtr();
			template <typename From> shared_ptr(const shared_ptr<From>& ref);
			T& operator*();
			T& operator[](unsigned i);
			T* operator->();
			shared_ptr<T>& operator=(T* val);
			shared_ptr<T>& operator=(T& val);
			shared_ptr<T>& operator=(const shared_ptr<T> &ref);
			template<typename From> shared_ptr<T>& operator=(const shared_ptr<From> &ref);
			shared_ptr<T>& operator=(std::nullptr_t);
			bool operator!=(const T* ref) const;
			bool operator==(const T* ref) const;
			bool operator!=(const shared_ptr<T> &ref) const;
			bool operator==(const shared_ptr<T> &ref) const;
			template<typename From> bool operator==(const shared_ptr<From> &ref);
			template<typename From> bool operator!=(const shared_ptr<From> &ref);
			T* free();
			T* getPtr()const;
			template<typename To> void copy(To* &ptr, int* &copies, std::mutex* &m) const;
		protected:
			void deletePtr();

		};

		template <typename T> shared_ptr<T> make_ptr(T* val) {
			shared_ptr<T> ret;
			ret = val;
			return ret;
		}

		template <typename T> shared_ptr<T> make_ptr(T& ref) {
			shared_ptr<T> ret;
			ret = ref;
			return ret;
		}

		template <typename T> bool operator==(const shared_ptr<T>& ref, std::nullptr_t) {
			return ref.getPtr() == nullptr;
		}

		template <typename T> bool operator==(std::nullptr_t, const shared_ptr<T>& ref) {
			return ref.getPtr() == nullptr;
		}

		template <typename T> bool operator!=(const shared_ptr<T>& ref, std::nullptr_t) {
			return ref.getPtr() != nullptr;
		}

		template <typename T> bool operator!=(std::nullptr_t, const shared_ptr<T>& ref) {
			return ref.getPtr() != nullptr;
		}
	}
}