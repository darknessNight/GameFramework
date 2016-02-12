#pragma once
#include "MemGuard.h"

namespace GF {
	namespace Core {
		template<typename T> void MemGuard<T>::init()
		{
			copies = new int;
			(*copies) = 1;
			userMutex = new std::mutex;
		}
		template<typename T>
		MemGuard<T>::MemGuard(T * val)
		{
			operator=(val);
		}

		template<typename T>
		MemGuard<T>::MemGuard(T & val){
			operator=(val);
		}

		template <typename T> MemGuard<T>::MemGuard(const MemGuard<T>& ref) {
			operator=(ref);
		}

		template <typename T> MemGuard<T>::MemGuard(std::nullptr_t) {
		}

		template <typename T> MemGuard<T>::~MemGuard() {
			std::lock_guard<std::mutex> guard(thsafe);
			deletePtr();
		}

		template<typename T>
		inline void MemGuard<T>::lockPtr()
		{
			if (userMutex == nullptr) throw std::runtime_error("Nullptr exception");
			userMutex->lock();
			uMutexId = std::this_thread::get_id();
		}

		template<typename T>
		inline void MemGuard<T>::unlockPtr()
		{
			if (userMutex == nullptr) throw std::runtime_error("Nullptr exception");
			uMutexId = std::thread::id();
			userMutex->unlock();
		}

		template <typename T> template <typename From> MemGuard<T>::MemGuard(const MemGuard<From>& ref) {
			operator=<From>(ref);
		}

		template <typename T> T& MemGuard<T>::operator*() {
			if (userMutex == nullptr || val==nullptr) throw std::runtime_error("Nullptr exception");
			if (uMutexId==std::this_thread::get_id())
				return *val;
			else {
				std::lock_guard<std::mutex> guard(thsafe);
				std::lock_guard<std::mutex> guard2(*userMutex);
				return *val;
			}
		}

		template<typename T> T& MemGuard<T>::operator[](unsigned i)
		{
			if (userMutex == nullptr || val == nullptr) throw std::runtime_error("Nullptr exception");
			if (uMutexId == std::this_thread::get_id())
				return *(val + i);
			else {
				std::lock_guard<std::mutex> guard(thsafe);
				std::lock_guard<std::mutex> guard2(*userMutex);
				return *(val + i);
			}
		}

		template <typename T> T* MemGuard<T>::operator->() {
			if (userMutex == nullptr || val == nullptr) throw std::runtime_error("Nullptr exception");
			if (uMutexId == std::this_thread::get_id())
				return val;
			else {
				std::lock_guard<std::mutex> guard(thsafe);
				std::lock_guard<std::mutex> guard2(*userMutex);
				return val;
			}
		}

		template <typename T> MemGuard<T>& MemGuard<T>::operator=(T* val) {
			std::lock_guard<std::mutex> guard(thsafe);
			deletePtr();
			init();
			this->val = val;
			deleting = true;
			return *this;
		}

		template <typename T> MemGuard<T>& MemGuard<T>::operator=(T& val) {
			std::lock_guard<std::mutex> guard(thsafe);
			deletePtr();
			init();
			this->val = &val;
			deleting = false;
			return *this;
		}

		template <typename T> MemGuard<T>& MemGuard<T>::operator=(const MemGuard<T> &ref) {
			std::lock_guard<std::mutex> guard(thsafe);
			deletePtr();

			copies = ref.copies;
			userMutex = ref.userMutex;
			if (copies != nullptr)
			(*copies)++;
			this->val = ref.val;
			deleting = ref.deleting;
			return *this;
		}

		template <typename T> template<typename From> MemGuard<T>& MemGuard<T>::operator=(const MemGuard<From> &ref) {
			std::lock_guard<std::mutex> guard(thsafe);
			deletePtr();
			ref.copy(val, copies, userMutex);
			if(copies!=nullptr)
				(*copies)++;
			deleting = ref.deleting;
			return *this;
		}

		template <typename T> MemGuard<T>& MemGuard<T>::operator=(std::nullptr_t) {
			std::lock_guard<std::mutex> guard(thsafe);
			deletePtr();
			if (copies != nullptr)
			copies = nullptr;
			this->val = nullptr;
			deleting = false;
			return *this;
		}

		template<typename T> bool MemGuard<T>::operator!=(const T * ref) const
		{
			return ref != val;
		}

		template<typename T> bool MemGuard<T>::operator==(const T * ref) const
		{
			return ref==val;
		}

		template<typename T> bool MemGuard<T>::operator!=(const MemGuard<T>& ref) const
		{
			return this->val != ref.val;
		}

		template <typename T> bool MemGuard<T>::operator==(const MemGuard<T> &ref) const {
			return this->val == ref.val;
		}

		template <typename T> template<typename From> bool MemGuard<T>::operator==(const MemGuard<From> &ref) {
			return (void*)ref.getPtr() == (void*)val;
		}

		template<typename T> template<typename From> bool MemGuard<T>::operator!=(const MemGuard<From>& ref)
		{
			return (void*)ref.getPtr() != (void*)val;
		}

		template <typename T> void MemGuard<T>::deletePtr() {
			if (copies == nullptr) return;
			(*copies)--;
			if ((*copies) <= 0) {
				delete copies;
				copies = nullptr;
				if (deleting && val != nullptr) {
					if (userMutex != nullptr)
						userMutex->lock();
					delete val;
					if (userMutex != nullptr)
						userMutex->unlock();
				}
				if (userMutex != nullptr)
					delete userMutex;
				userMutex = nullptr;
			}
		}

		template <typename T> T* MemGuard<T>::free() {
			std::lock_guard<std::mutex> guard(thsafe);
			if (copies != nullptr)
			delete copies;
			return val;
		}

		template <typename T> T* MemGuard<T>::getPtr()const {
			return val;
		}

		template<typename T> template<typename To> void MemGuard<T>::copy(To *& ptr, int *& copies, std::mutex *& m) const
		{
			ptr = val;
			copies = this->copies;
			m = userMutex;
		}


	}
}