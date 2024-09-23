module;

#include <cstddef>
#include <deque>

export module dsa:Stack;


namespace dsa {

    /**
     * @brief Implements a simple LIFO stack.
     */
    export template <typename T>
    class Stack {
    public:

        /** @name Element insertion/retrieval */
        /** @{ */
        [[nodiscard]]
        auto top() const noexcept -> const T& {
            return data_.back();
        }


        [[nodiscard]]
        auto top() noexcept -> T& {
            return data_.back();
        }


        void push(const T& value) {
            data_.push_back(value);
        }


        void push(T&& value) {
            data_.push_back(std::move(value));
        }


        [[nodiscard]]
        auto pop() noexcept -> T {
            auto value = std::move(data_.back());
            data_.pop_back();
            return value;
        }
        /** @} */


        /** @name Stack size */
        /** @{ */
        [[nodiscard]]
        auto size() const noexcept -> std::size_t {
            return data_.size();
        }


        [[nodiscard]]
        auto isEmpty() const noexcept -> bool {
            return size() == 0;
        }
        /** @} */


    private:
        std::deque<T> data_;
    };

}
