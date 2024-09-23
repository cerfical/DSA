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
    auto linearSearch(const R& rng, const T& val) {
        const auto end = std::ranges::end(rng);
        for(auto it = std::ranges::begin(rng); it != end; it++) {
            if(*it == val) {
                return it;
            }
        }
        return end;
    }


    /**
     * @brief Performs an iterative binary search on a sorted range of values in @f$O(\lg n)@f$ time.
     */
    export template <std::ranges::forward_range R, typename T>
    auto binarySearch(const R& rng, const T& val) {
        const auto end = std::ranges::end(rng);
        auto left = std::ranges::begin(rng);
        auto right = end;

        while(left != right) {
            const auto mid = left + (std::distance(left, right) / 2);
            if(*mid == val) {
                return mid;
            }

            if(*mid > val) {
                right = mid;
            } else if(*mid < val) {
                left = mid + 1;
            }
        }

        return end;
    }
    /** @} */

}
