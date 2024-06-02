#ifndef DSA_LIST_CONST_ITERATOR_HEADER
#define DSA_LIST_CONST_ITERATOR_HEADER

#include "ListNode.hpp"
#include <cassert>

namespace dsa {
	
	template <typename T>
	class List;

	/**
	 * @brief Provides read-only access to elements of a List.
	 */
	template <typename T>
	class ListConstIterator {
	public:

		friend bool operator==(const ListConstIterator&, const ListConstIterator&) = default;



		ListConstIterator() = default;

		ListConstIterator(const List<T>* list, const ListNode<T>* node) noexcept
			: m_currentNode(node), m_list(list)
		{ }


		ListConstIterator(const ListConstIterator&) = default;
		
		ListConstIterator& operator=(const ListConstIterator&) = default;



		ListConstIterator& operator++() noexcept {
			assert(m_currentNode && "Incrementing an empty iterator");
			assert(*this != m_list->end() && "Attempting to go beyond the list end");

			m_currentNode = m_currentNode->next;
			return *this;
		}

		ListConstIterator operator++(int) noexcept {
			const auto it = *this;
			operator++();
			return it;
		}


		ListConstIterator& operator--() noexcept {
			assert(m_currentNode && "Decrementing an empty iterator");
			assert(*this != m_list->begin() && "Attempting to go beyond the beginning of a list");

			m_currentNode = m_currentNode->prev;
			return *this;
		}

		ListConstIterator operator--(int) noexcept {
			const auto it = *this;
			operator--();
			return it;
		}


		const T& operator*() const noexcept {
			assert(m_currentNode && "Dereferencing an empty iterator");
			assert(*this != m_list->end() && "Dereferencing an end iterator");

			return m_currentNode->value;
		}

		const T* operator->() const noexcept {
			return &operator*();
		}



	private:
		const ListNode<T>* m_currentNode = {};
		const List<T>* m_list = {};
	};

}

#endif
