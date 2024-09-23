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
        const T& front() const noexcept {
            return data_.front();
        }

        const T& back() const noexcept {
            return data_.back();
        }


        T& front() noexcept {
            return data_.front();
        }

        T& back() noexcept {
            return data_.back();
        }


        void push(const T& value) {
            data_.push_back(value);
        }

        void push(T&& value) {
            data_.push_back(std::move(value));
        }

        T pop() {
            auto value = std::move(data_.front());
            data_.pop_front();
            return value;
        }
        /** @} */


        /** @name Queue size */
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
