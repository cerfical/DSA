#pragma once

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


        ListConstIterator(const ListConstIterator&) = default;
        ListConstIterator& operator=(const ListConstIterator&) = default;

        ListConstIterator(ListConstIterator&&) = default;
        ListConstIterator& operator=(ListConstIterator&&) = default;


        ListConstIterator(const List<T>* list, const ListNode<T>* node) noexcept
            : currentNode_(node), list_(list) {}

        ListConstIterator() noexcept = default;
        ~ListConstIterator() = default;


        ListConstIterator& operator++() noexcept {
            assert(currentNode_ && "Incrementing an empty iterator");
            assert(*this != list_->end() && "Attempting to go beyond the list end");

            currentNode_ = currentNode_->next;
            return *this;
        }


        ListConstIterator operator++(int) noexcept {
            const auto it = *this;
            operator++();
            return it;
        }


        ListConstIterator& operator--() noexcept {
            assert(currentNode_ && "Decrementing an empty iterator");
            assert(*this != list_->begin() && "Attempting to go beyond the beginning of a list");

            currentNode_ = currentNode_->prev;
            return *this;
        }


        ListConstIterator operator--(int) noexcept {
            const auto it = *this;
            operator--();
            return it;
        }


        const T& operator*() const noexcept {
            assert(currentNode_ && "Dereferencing an empty iterator");
            assert(*this != list_->end() && "Dereferencing an end iterator");

            return currentNode_->value;
        }


        const T* operator->() const noexcept {
            return &operator*();
        }


    private:
        const ListNode<T>* currentNode_ = {};
        const List<T>* list_ = {};
    };

}
