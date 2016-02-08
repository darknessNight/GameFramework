#pragma once


namespace GF {
	namespace Core {
		class Object {};

		template <typename T> class MemGuard {//TODO add mutex and modyfi for thread safe
		protected:
			int* copies = nullptr;
			T* val = nullptr;
		public:
			bool deleting = false;

			MemGuard() = default;
			MemGuard(const MemGuard<T>& ref) {
				operator=(ref);
			}

			MemGuard(std::nullptr_t) {
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

			void deletePtr() {
				(*copies)--;
				if ((*copies) <= 0) {
					delete copies;
					copies = nullptr;
					if (deleting && val!=nullptr) {
						delete val;
					}
				}
			}

			~MemGuard() {
				if (copies != nullptr) {
					deletePtr();
				}
			}

			void operator=(T* val) {
				if (copies != nullptr) {
					deletePtr();
				}
				copies = new int;
				(*copies) = 1;
				this->val = val;
				deleting = true;
			}

			void operator=(T& val) {
				if (copies != nullptr) {
					deletePtr();
				}
				copies = new int;
				(*copies) = 1;
				this->val = &val;
				deleting = false;
			}

			void operator=(const MemGuard<T> &ref) {
				if (copies != nullptr && copies != ref.copies) {
					deletePtr();
				}
				copies = ref.copies;
				(*copies)++;
				this->val = ref.val;
				deleting = ref.deleting;
			}

			template<typename From> void operator=(const MemGuard<From> &ref) {
				if (copies != nullptr && copies != ref.getCount()) {
					deletePtr();
				}
				copies = const_cast<int*>(ref.getCount());
				(*copies)++;
				this->val = static_cast<T*>(const_cast<From*>(ref.getPtr()));
				deleting = ref.deleting;
			}

			template<typename From> bool operator==(const MemGuard<From> &ref) {
				return ref.getPtr() == val;
			}

			void operator=(std::nullptr_t) {
				if (copies != nullptr) {
					deletePtr();
				}
				copies = nullptr;
				this->val = nullptr;
				deleting = false;
			}

			T* free() {
				delete copies;
				return val;
			}

			bool operator==(const MemGuard<T> &ref) const {
				return this->val == ref.val;
			}

			const T* getPtr()const {
				return val;
			}

			const int* const getCount()const {
				return copies;
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