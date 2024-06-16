#pragma once

#include "ListConstIterator.hpp"
#include "ListIterator.hpp"
#include "ListNode.hpp"

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <ostream>

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
            other.head_.prev->next = &head_;
            other.head_.next->prev = &head_;

            head_.next = other.head_.next;
            head_.prev = other.head_.prev;
            head_.value = other.head_.value;

            std::construct_at(&other);
        }


        List& operator=(List&& other) noexcept {
            assert(this != &other && "Self move-assignment");

            std::destroy_at(this);
            std::construct_at(this, std::move(other));

            return *this;
        }


        List(std::initializer_list<T> values) {
            for(const auto& v : values) {
                pushBack(v);
            }
        }


        List() noexcept = default;

        ~List() {
            clear();
        }


        /** @name Element insertion */
        /** @{ */
        void pushFront(const T& value) {
            insertNode(value, head());
        }

        void pushFront(T&& value) {
            insertNode(std::move(value), head());
        }


        void pushBack(const T& value) {
            insertNode(value, head()->prev);
        }

        void pushBack(T&& value) {
            insertNode(std::move(value), head()->prev);
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
            return head_.value;
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
            return ListIterator(this, head()->next);
        }


        ListConstIterator<T> cend() const noexcept {
            return end();
        }

        ListConstIterator<T> end() const noexcept {
            return const_cast<List*>(this)->end();
        }

        ListIterator<T> end() noexcept {
            return ListIterator(this, head());
        }
        /** @} */


    private:

        template <typename S>
        void insertNode(S&& value, ListNode<T>* prev) {
            auto* const n = new ListNode<T>(prev, prev->next, std::forward<S>(value));

            prev->next->prev = n;
            prev->next = n;

            head_.value++;
        }

        void deleteNode(ListNode<T>* n) {
            n->prev->next = n->next;
            n->next->prev = n->prev;
            head_.value--;

            delete n;
        }


        ListNode<T>* nodeAtTail() const noexcept {
            assert(!isEmpty() && "Attempting to read an element from the end of an empty list");
            return head()->prev;
        }

        ListNode<T>* nodeAtHead() const noexcept {
            assert(!isEmpty() && "Attempting to read an element from the beginning of an empty list");
            return head()->next;
        }


        ListNode<T>* head() noexcept {
            return reinterpret_cast<ListNode<T>*>(&head_);
        }

        const ListNode<T>* head() const noexcept {
            return const_cast<List*>(this)->head();
        }


        ListNode<std::size_t> makeListHead() noexcept {
            return { &head_, &head_, 0 };
        }


        ListNode<std::size_t> head_ = makeListHead();
    };

}
