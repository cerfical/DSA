#pragma once

#include <cstddef>
#include <deque>

namespace dsa {

    /**
     * @brief Implements a simple LIFO stack.
     */
    template <typename T>
    class Stack {
    public:

        /** @name Element insertion/retrieval */
        /** @{ */
        const T& top() const noexcept {
            return data_.back();
        }

        T& top() noexcept {
            return data_.back();
        }


        void push(const T& value) {
            data_.push_back(value);
        }

        void push(T&& value) {
            data_.push_back(std::move(value));
        }

        T pop() {
            auto value = std::move(data_.back());
            data_.pop_back();
            return value;
        }
        /** @} */


        /** @name Stack size */
        /** @{ */
        std::size_t size() const noexcept {
            return data_.size();
        }

        bool isEmpty() const noexcept {
            return size() == 0;
        }
        /** @} */


    private:
        std::deque<T> data_;
    };

}
