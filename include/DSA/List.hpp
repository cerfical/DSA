#ifndef DSA_LIST_HEADER
#define DSA_LIST_HEADER

#include <cstddef>
#include <memory>
#include <initializer_list>
#include <cassert>

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

		friend bool operator==(const List& lhs, const List& rhs) {
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



		class ConstIterator;
		class Iterator;



		List() = default;
		
		List(std::initializer_list<T> values) {
			for(auto& v : values) {
				pushBack(std::move(v));
			}
		}

		~List() {
			clear();
		}



		List(const List& other) {
			for(const auto& val : other) {
				pushBack(val);
			}
		}

		List& operator=(const List& other) {
			assert(this != &other && "Self copy-assignment");

			std::destroy_at(this);
			std::construct_at(this, other);

			return *this;
		}



		List(List&& other) noexcept {
			// fix head and tail pointers
			other.m_head.prev->next = &m_head;
			other.m_head.next->prev = &m_head;
			
			m_head.next = other.m_head.next;
			m_head.prev = other.m_head.prev;
			m_size = other.m_size;

			std::construct_at(&other);
		}

		List& operator=(List&& other) noexcept {
			assert(this != &other && "Self move-assignment");

			std::destroy_at(this);
			std::construct_at(this, std::move(other));
			
			return *this;
		}



		void pushFront(const T& value) {
			pushFront(T(value));
		}

		void pushFront(T&& value) {
			insertNode(std::move(value), &m_head);
		}

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



		void pushBack(const T& value) {
			pushBack(T(value));
		}

		void pushBack(T&& value) {
			insertNode(std::move(value), m_head.prev);
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



		void clear() {
			while(!isEmpty()) {
				deleteNode(nodeAtTail());
			}
		}

		std::size_t size() const noexcept {
			return m_size;
		}

		bool isEmpty() const noexcept {
			return size() == 0;
		}



		ConstIterator cbegin() const noexcept {
			return begin();
		}

		ConstIterator begin() const noexcept {
			return const_cast<List*>(this)->begin();
		}

		Iterator begin() noexcept {
			return Iterator(*this, m_head.next);
		}



		ConstIterator cend() const noexcept {
			return end();
		}

		ConstIterator end() const noexcept {
			return const_cast<List*>(this)->end();
		}

		Iterator end() noexcept {
			return Iterator(*this, &m_head);
		}



	private:

		struct Node {
			
			/** @brief Creates a list head node. */
			Node() noexcept
				: prev(this), next(this)
			{ }
			
			/** @brief Creates a list node with a value. */
			Node(T&& value)
				: value(std::move(value))
			{ }
			
			~Node()
			{ }


			Node(const Node&) = delete;
			Node& operator=(const Node&) = delete;


			union {
				std::byte unused_[sizeof(T)] = {};
				T value;
			};
			

			Node* prev = nullptr;
			Node* next = nullptr;

		};


		void insertNode(T&& value, Node* prev) {
			auto n = std::make_unique<Node>(std::move(value));

			n->prev = prev;
			n->next = prev->next;

			prev->next->prev = n.get();
			prev->next = n.release();
			
			m_size++;
		}

		void deleteNode(Node* n) {
			n->prev->next = n->next;
			n->next->prev = n->prev;
			m_size--;

			// manually call the destructor since the value is stored in a union
			std::destroy_at(&n->value);
			delete n;
		}


		Node* nodeAtTail() const noexcept {
			assert(!isEmpty() && "Attempting to read an element from the end of an empty list");
			return m_head.prev;
		}

		Node* nodeAtHead() const noexcept {
			assert(!isEmpty() && "Attempting to read an element from the beginning of an empty list");
			return m_head.next;
		}


		std::size_t m_size = 0;
		Node m_head;

	};



	template <typename T>
	class List<T>::ConstIterator {
		friend List;

	public:

		friend bool operator==(const ConstIterator&, const ConstIterator&) = default;


		ConstIterator() = default;

		ConstIterator(const ConstIterator&) = default;
		ConstIterator& operator=(const ConstIterator&) = default;


		ConstIterator& operator++() noexcept {
			assert(m_currentNode && "Incrementing an empty iterator");
			assert(*this != m_list->end() && "Attempting to go beyond the list end");

			m_currentNode = m_currentNode->next;
			return *this;
		}

		ConstIterator operator++(int) noexcept {
			const auto it = *this;
			operator++();
			return it;
		}


		ConstIterator& operator--() noexcept {
			assert(m_currentNode && "Decrementing an empty iterator");
			assert(*this != m_list->begin() && "Attempting to go beyond the beginning of a list");

			m_currentNode = m_currentNode->prev;
			return *this;
		}

		ConstIterator operator--(int) noexcept {
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

		ConstIterator(const List& list, const Node* n) noexcept
			: m_currentNode(n), m_list(&list)
		{ }

		const Node* m_currentNode = {};
		const List* m_list = {};

	};



	template <typename T>
	class List<T>::Iterator : public ConstIterator {
		friend List;

	public:

		Iterator() = default;
		
		Iterator(const Iterator&) = default;
		Iterator& operator=(const Iterator&) = default;


		Iterator& operator++() noexcept {
			ConstIterator::operator++();
			return *this;
		}

		Iterator operator++(int) noexcept {
			const auto it = *this;
			operator++();
			return it;
		}


		Iterator& operator--() noexcept {
			ConstIterator::operator--();
			return *this;
		}

		Iterator operator--(int) noexcept {
			const auto it = *this;
			operator--();
			return it;
		}


		const T& operator*() const noexcept {
			return ConstIterator::operator*();
		}

		T& operator*() noexcept {
			return const_cast<T&>(static_cast<const Iterator*>(this)->operator*());
		}


		const T* operator->() const noexcept {
			return ConstIterator::operator->();
		}

		T* operator->() noexcept {
			return const_cast<T&>(static_cast<const Iterator*>(this)->operator->());
		}


	private:

		Iterator(const List& list, const Node* n) noexcept
			: ConstIterator(list, n)
		{ }

	};

}

#endif
