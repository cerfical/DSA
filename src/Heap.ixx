module;

#include <cstddef>
#include <vector>

export module dsa:Heap;

import :heap_util;


namespace dsa {

    /**
     * @brief Implements a fast queue that gives priority to 'larger' elements first.
     */
    export template <typename T>
    class Heap {
    public:

        /** @name Element insertion/retrieval */
        /** @{ */
        [[nodiscard]]
        auto top() const noexcept -> const T& {
            return data_.front();
        }


        void push(const T& value) {
            data_.push_back(value);
            heap_util::insertLast(data_);
        }


        void push(T&& value) {
            data_.push_back(std::move(value));
            heap_util::insertLast(data_);
        }


        [[nodiscard]]
        auto pop() noexcept -> T {
            auto value = heap_util::extractTop(data_);
            data_.pop_back();
            return value;
        }
        /** @} */


        /** @name Heap size */
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
        std::vector<T> data_;
    };

}
