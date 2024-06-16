#pragma once

#include "HeapUtil.hpp"

#include <vector>

namespace dsa {

    /**
     * @brief Implements a fast queue that gives priority to 'larger' elements first.
     */
    template <typename T>
    class Heap {
    public:

        Heap& operator=(const Heap&) = default;
        Heap& operator=(Heap&&) = default;


        /** @name Heap initialization */
        /** @{ */
        Heap() = default;

        Heap(const Heap&) = default;
        Heap(Heap&&) = default;
        /** @} */


        /** @name Element insertion/retrieval */
        /** @{ */
        const T& top() const noexcept {
            return data_.front();
        }

        void push(const T& value) {
            data_.push_back(value);
            HeapUtil::insertLast(data_);
        }

        void push(T&& value) {
            data_.push_back(std::move(value));
            HeapUtil::insertLast(data_);
        }

        T pop() {
            auto value = HeapUtil::extractTop(data_);
            data_.pop_back();
            return value;
        }
        /** @} */


        /** @name Heap size */
        /** @{ */
        std::size_t size() const noexcept {
            return data_.size();
        }

        bool isEmpty() const noexcept {
            return size() == 0;
        }
        /** @} */


    private:
        std::vector<T> data_;
    };

}
