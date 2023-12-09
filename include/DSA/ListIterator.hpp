#ifndef DSA_LIST_ITERATOR_HEADER
#define DSA_LIST_ITERATOR_HEADER

#include "ListConstIterator.hpp"

namespace dsa {

	/**
	 * @brief Opens a List for reading and mutating its elements.
	 */
	template <typename T>
	class ListIterator : public ListConstIterator<T> {
	public:

		ListIterator() = default;

		ListIterator(List<T>* list, ListNode<T>* node) noexcept
			: ListConstIterator<T>(list, node)
		{ }



		ListIterator& operator++() noexcept {
			ListConstIterator<T>::operator++();
			return *this;
		}

		ListIterator operator++(int) noexcept {
			const auto it = *this;
			operator++();
			return it;
		}


		ListIterator& operator--() noexcept {
			ListConstIterator<T>::operator--();
			return *this;
		}

		ListIterator operator--(int) noexcept {
			const auto it = *this;
			operator--();
			return it;
		}


		const T& operator*() const noexcept {
			return ListConstIterator<T>::operator*();
		}

		T& operator*() noexcept {
			return const_cast<T&>(static_cast<const ListIterator*>(this)->operator*());
		}


		const T* operator->() const noexcept {
			return ListConstIterator<T>::operator->();
		}

		T* operator->() noexcept {
			return const_cast<T&>(static_cast<const ListIterator*>(this)->operator->());
		}

	};

}

#endif
