#pragma once

#include "ListConstIterator.hpp"
#include "ListNode.hpp"

namespace dsa {

    /**
     * @brief Opens a List for reading and mutating its elements.
     */
    template <typename T>
    class ListIterator : public ListConstIterator<T> {
    public:

        ListIterator(List<T>* list, ListNode<T>* node) noexcept
            : ListConstIterator<T>(list, node) {}

        ListIterator() noexcept = default;


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


        T& operator*() const noexcept {
            return const_cast<T&>(ListConstIterator<T>::operator*());
        }


        T* operator->() const noexcept {
            return &operator*();
        }
    };

}
