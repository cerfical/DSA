#ifndef DSA_SEARCH_HEADER
#define DSA_SEARCH_HEADER

#include <ranges>
#include <iterator>
#include <utility>

namespace dsa {

	/**
	 * @brief Performs a search on a range of values in O(n) time.
	 */
	template <std::ranges::forward_range R, typename T>
	auto linearSearch(R&& range, T&& searchValue) {
		for(auto it = range.begin(); it != range.end(); it++) {
			if(*it == searchValue) {
				return it;
			}
		}
		return range.end();
	}



	/**
	 * @brief Performs a search on a sorted range of values in O(lg n) time.
	 */
	template <std::ranges::forward_range R, typename T>
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

}

#endif
