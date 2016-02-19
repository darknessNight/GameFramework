#pragma once
#include <mutex>

namespace GF {
	namespace Core {

		template <typename T> class MemGuard {
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

			MemGuard() = default;
			MemGuard(T* val);
			MemGuard(T& val);
			MemGuard(const MemGuard<T>& ref);
			MemGuard(std::nullptr_t);
			~MemGuard();
			void lockPtr();
			void unlockPtr();
			template <typename From> MemGuard(const MemGuard<From>& ref);
			T& operator*();
			T& operator[](unsigned i);
			T* operator->();
			MemGuard<T>& operator=(T* val);
			MemGuard<T>& operator=(T& val);
			MemGuard<T>& operator=(const MemGuard<T> &ref);
			template<typename From> MemGuard<T>& operator=(const MemGuard<From> &ref);
			MemGuard<T>& operator=(std::nullptr_t);
			bool operator!=(const T* ref) const;
			bool operator==(const T* ref) const;
			bool operator!=(const MemGuard<T> &ref) const;
			bool operator==(const MemGuard<T> &ref) const;
			template<typename From> bool operator==(const MemGuard<From> &ref);
			template<typename From> bool operator!=(const MemGuard<From> &ref);
			T* free();
			T* getPtr()const;
			template<typename To> void copy(To* &ptr, int* &copies, std::mutex* &m) const;
		protected:
			void deletePtr();

		};

		template <typename T> MemGuard<T> make_ptr(T* val) {
			MemGuard<T> ret;
			ret = val;
			return ret;
		}

		template <typename T> MemGuard<T> make_ptr(T& ref) {
			MemGuard<T> ret;
			ret = ref;
			return ret;
		}

		template <typename T> bool operator==(const MemGuard<T>& ref, std::nullptr_t) {
			return ref.getPtr() == nullptr;
		}

		template <typename T> bool operator==(std::nullptr_t, const MemGuard<T>& ref) {
			return ref.getPtr() == nullptr;
		}

		template <typename T> bool operator!=(const MemGuard<T>& ref, std::nullptr_t) {
			return ref.getPtr() != nullptr;
		}

		template <typename T> bool operator!=(std::nullptr_t, const MemGuard<T>& ref) {
			return ref.getPtr() != nullptr;
		}
	}
}