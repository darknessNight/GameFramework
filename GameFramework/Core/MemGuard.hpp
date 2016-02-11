#pragma once
#include "MemGuard.h"

namespace GF {
	namespace Core {
		template<typename T>
		MemGuard<T>::MemGuard(T * val)
		{
			operator=(val);
		}

		template<typename T>
		MemGuard<T>::MemGuard(T & val)
		{
			operator=(val);
		}

		template <typename T> MemGuard<T>::MemGuard(const MemGuard<T>& ref) {
			operator=(ref);
		}

		template <typename T> MemGuard<T>::MemGuard(std::nullptr_t) {
		}

		template <typename T> MemGuard<T>::~MemGuard() {
			deletePtr();
		}

		template <typename T> template <typename From> MemGuard<T>::MemGuard(const MemGuard<From>& ref) {
			operator=<From>(ref);
		}

		template <typename T> T& MemGuard<T>::operator*() {
			return *val;
		}

		template <typename T> T* MemGuard<T>::operator->() {
			return val;
		}

		template <typename T> MemGuard<T>& MemGuard<T>::operator=(T* val) {
			deletePtr();
			copies = new int;
			(*copies) = 1;
			this->val = val;
			deleting = true;
			return *this;
		}

		template <typename T> MemGuard<T>& MemGuard<T>::operator=(T& val) {
			deletePtr();
			copies = new int;
			(*copies) = 1;
			this->val = &val;
			deleting = false;
			return *this;
		}

		template <typename T> MemGuard<T>& MemGuard<T>::operator=(const MemGuard<T> &ref) {
			deletePtr();
			copies = ref.copies;
			if (copies != nullptr)
			(*copies)++;
			this->val = ref.val;
			deleting = ref.deleting;
			return *this;
		}

		template <typename T> template<typename From> MemGuard<T>& MemGuard<T>::operator=(const MemGuard<From> &ref) {
			if (copies != nullptr && copies != ref.getCount()) {
				deletePtr();
			}
			copies = const_cast<int*>(ref.getCount());
			if(copies!=nullptr)
				(*copies)++;
			this->val = static_cast<T*>(const_cast<From*>(ref.getPtr()));
			deleting = ref.deleting;
			return *this;
		}

		template <typename T> MemGuard<T>& MemGuard<T>::operator=(std::nullptr_t) {
			deletePtr();
			if (copies != nullptr)
			copies = nullptr;
			this->val = nullptr;
			deleting = false;
			return *this;
		}

		template <typename T> bool MemGuard<T>::operator==(const MemGuard<T> &ref) const {
			return this->val == ref.val;
		}

		template <typename T> template<typename From> bool MemGuard<T>::operator==(const MemGuard<From> &ref) {
			return (void*)ref.getPtr() == (void*)val;
		}

		template <typename T> void MemGuard<T>::deletePtr() {
			if (copies == nullptr) return;
			(*copies)--;
			if ((*copies) <= 0) {
				delete copies;
				copies = nullptr;
				if (deleting && val != nullptr) {
					delete val;
				}
			}
		}

		template <typename T> T* MemGuard<T>::free() {
			if (copies != nullptr)
			delete copies;
			return val;
		}

		template <typename T> const T* MemGuard<T>::getPtr()const {
			return val;
		}

		template <typename T> const int* const MemGuard<T>::getCount()const {
			return copies;
		}
	}
}