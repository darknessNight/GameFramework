#pragma once


namespace GF {
	namespace Core {
		class Object {};

		template <typename T> struct MemGuard {
			bool deleting = false;
			int* copies=nullptr;
			T* val=nullptr;

			MemGuard() = default;
			MemGuard(const MemGuard<T>& ref) {
				operator=(ref);
			}

			template <typename From> MemGuard(const MemGuard<From>& ref) {
				operator=<From>(ref);
			}

			T& operator*() {
				return *val;
			}

			T* operator->() {
				return val;
			}

			~MemGuard(){
				if (copies != nullptr) {
					(*copies)--;
					if ((*copies) == 0) {
						delete copies;
						copies == nullptr;
						if (deleting) {
							delete val;
						}
					}
				}
			}

			void operator=(T* val) {
				if(copies==nullptr)
					copies = new int;
				(*copies) = 1;
				this->val = val;
				deleting = true;
			}

			void operator=(T& val) {
				if (copies == nullptr)
					copies = new int;
				(*copies) = 1;
				this->val = &val;
				deleting = false;
			}

			void operator=(const MemGuard<T> &ref) {
				copies = ref.copies;
				(*copies)++;
				this->val = ref.val;
				deleting = ref.deleting;
			}

			template<typename From> void operator=(const MemGuard<From> &ref) {
				copies = ref.copies;
				(*copies)++;
				this->val = ref.val;
				deleting = ref.deleting;
			}

			T* free() {
				delete copies;
				return val;
			}
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
	}
}