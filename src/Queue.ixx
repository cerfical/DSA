module;

#include <cstddef>
#include <deque>

export module dsa:Queue;


namespace dsa {

    /**
     * @brief Implements a simple FIFO queue.
     */
    export template <typename T>
    class Queue {
    public:

        /** @name Element insertion/retrieval */
        /** @{ */
        [[nodiscard]]
        auto front() const noexcept -> const T& {
            return data_.front();
        }


        [[nodiscard]]
        auto back() const noexcept -> const T& {
            return data_.back();
        }


        [[nodiscard]]
        auto front() noexcept -> T& {
            return data_.front();
        }


        [[nodiscard]]
        auto back() noexcept -> T& {
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
            auto value = std::move(data_.front());
            data_.pop_front();
            return value;
        }
        /** @} */


        /** @name Queue size */
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
