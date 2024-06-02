#pragma once

#include "ListIterator.hpp"

#include <ostream>
#include <initializer_list>
#include <cassert>
#include <memory>

namespace dsa {

	/**
	 * @brief Implements a doubly linked list.
	 */
	template <typename T>
	class List {
	public:

		friend std::ostream& operator<<(std::ostream& out, const List& list) {
			out << "{ ";
			for(const auto& val : list) {
				out << val << ' ';
			}
			out << '}';
			return out;
		}

		friend bool operator==(const List& lhs, const List& rhs) noexcept {
			if(lhs.size() != rhs.size()) {
				return false;
			}

			for(auto rhsIt = rhs.begin(); const auto& val : lhs) {
				if(val != *rhsIt) {
					return false;
				}
				rhsIt++;
			}

			return true;
		}



		List& operator=(const List& other) {
			assert(this != &other && "Self copy-assignment");

			std::destroy_at(this);
			std::construct_at(this, other);

			return *this;
		}

		List& operator=(List&& other) noexcept {
			assert(this != &other && "Self move-assignment");

			std::destroy_at(this);
			std::construct_at(this, std::move(other));

			return *this;
		}


		~List() {
			clear();
		}



		/** @name List creation */
		/** @{ */
		List() noexcept {
			m_head.prev = m_head.next = &m_head;
		}
		
		List(std::initializer_list<T> values) : List() {
			for(const auto& v : values) {
				pushBack(v);
			}
		}


		List(const List& other) : List() {
			for(const auto& val : other) {
				pushBack(val);
			}
		}

		List(List&& other) noexcept : List() {
			other.m_head.prev->next = &m_head;
			other.m_head.next->prev = &m_head;
			
			m_head.next = other.m_head.next;
			m_head.prev = other.m_head.prev;
			m_size = other.m_size;

			std::construct_at(&other);
		}
		/** @} */



		/** @name Element insertion */
		/** @{ */
		void pushFront(const T& value) {
			makeNode(value, &m_head);
		}

		void pushFront(T&& value) {
			makeNode(std::move(value), &m_head);
		}


		void pushBack(const T& value) {
			makeNode(value, m_head.prev);
		}

		void pushBack(T&& value) {
			makeNode(std::move(value), m_head.prev);
		}
		/** @} */



		/** @name Element retrieval */
		/** @{ */
		T popFront() {
			auto val = std::move(nodeAtHead()->value);
			deleteNode(nodeAtHead());
			return val;
		}
		
		const T& front() const noexcept {
			return nodeAtHead()->value;
		}

		T& front() noexcept {
			return nodeAtHead()->value;
		}


		T popBack() {
			auto val = std::move(nodeAtTail()->value);
			deleteNode(nodeAtTail());
			return val;
		}

		const T& back() const noexcept {
			return nodeAtTail()->value;
		}

		T& back() noexcept {
			return nodeAtTail()->value;
		}
		/** @} */



		/** @name List state */
		/** @{ */
		std::size_t size() const noexcept {
			return m_size;
		}

		bool isEmpty() const noexcept {
			return size() == 0;
		}

		void clear() {
			while(!isEmpty()) {
				deleteNode(nodeAtTail());
			}
		}
		/** @} */



		/** @name Iteration support */
		/** @{ */
		ListConstIterator<T> cbegin() const noexcept {
			return begin();
		}

		ListConstIterator<T> begin() const noexcept {
			return const_cast<List*>(this)->begin();
		}

		ListIterator<T> begin() noexcept {
			return ListIterator(this, m_head.next);
		}


		ListConstIterator<T> cend() const noexcept {
			return end();
		}

		ListConstIterator<T> end() const noexcept {
			return const_cast<List*>(this)->end();
		}

		ListIterator<T> end() noexcept {
			return ListIterator(this, &m_head);
		}
		/** @} */



	private:

		template <typename S>
		void makeNode(S&& value, ListNode<T>* prev) {
			auto n = std::make_unique<ListNode<T>>(
				std::forward<S>(value), prev, prev->next
			);
			insertNode(n.release(), prev);
		}

		void insertNode(ListNode<T>* n, ListNode<T>* prev) {
			prev->next->prev = n;
			prev->next = n;
			m_size++;
		}

		void deleteNode(ListNode<T>* n) {
			n->prev->next = n->next;
			n->next->prev = n->prev;
			m_size--;

			delete n;
		}


		ListNode<T>* nodeAtTail() const noexcept {
			assert(!isEmpty() && "Attempting to read an element from the end of an empty list");
			return m_head.prev;
		}

		ListNode<T>* nodeAtHead() const noexcept {
			assert(!isEmpty() && "Attempting to read an element from the beginning of an empty list");
			return m_head.next;
		}



		std::size_t m_size = 0;

		union {
			std::byte m_unused[sizeof(ListNode<T>)] = {};
			ListNode<T> m_head;
		};

	};

}
