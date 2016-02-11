#pragma once

namespace GF {
	namespace Core {

		template <typename T> class MemGuard {//TODO add mutex and modyfi for thread safe
		protected:
			int* copies = nullptr;
			T* val = nullptr;
		public:
			bool deleting = false;

			MemGuard() = default;
			MemGuard(T* val);
			MemGuard(T& val);
			MemGuard(const MemGuard<T>& ref);
			MemGuard(std::nullptr_t);
			~MemGuard();
			template <typename From> MemGuard(const MemGuard<From>& ref);
			T& operator*();
			T* operator->();
			MemGuard<T>& operator=(T* val);
			MemGuard<T>& operator=(T& val);
			MemGuard<T>& operator=(const MemGuard<T> &ref);
			template<typename From> MemGuard<T>& operator=(const MemGuard<From> &ref);
			MemGuard<T>& operator=(std::nullptr_t);
			bool operator==(const MemGuard<T> &ref) const;
			template<typename From> bool operator==(const MemGuard<From> &ref);
			void deletePtr();
			T* free();
			const T* getPtr()const;
			const int* const getCount()const;
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