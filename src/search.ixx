module;

#include <ranges>

export module dsa:search;


namespace dsa {

    /** @name Search */
    /** @{ */
    /**
     * @brief Performs an ordinary linear search on a range of values in @f$O(n)@f$ time.
     */
    export template <std::ranges::forward_range R, typename T>
    auto linearSearch(R&& range, T&& searchValue) {
        for(auto it = range.begin(); it != range.end(); it++) {
            if(*it == searchValue) {
                return it;
            }
        }
        return range.end();
    }


    /**
     * @brief Performs an iterative binary search on a sorted range of values in @f$O(\lg n)@f$ time.
     */
    export template <std::ranges::forward_range R, typename T>
    auto binarySearch(R&& range, T&& searchValue) {
        auto left = range.begin();
        auto right = range.end();

        while(left != right) {
            const auto mid = left + std::distance(left, right) / 2;
            const auto& value = *mid;

            if(value == searchValue) {
                return mid;
            }

            if(value > searchValue) {
                right = mid;
            } else if(value < searchValue) {
                left = mid + 1;
            }
        }

        return range.end();
    }
    /** @} */

}
