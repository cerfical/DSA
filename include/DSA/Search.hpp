#ifndef DSA_SEARCH_HEADER
#define DSA_SEARCH_HEADER

#include <ranges>
#include <iterator>
#include <utility>

namespace dsa {

	/**
	 * @brief Performs a search on a range of values in O(n) time.
	 */
	template <std::ranges::random_access_range R, typename T>
	auto linearSearch(R&& range, T&& value) {
		for(auto it = range.begin(); it != range.end(); it++) {
			if(*it == value) {
				return it;
			}
		}
		return range.end();
	}



	/**
	 * @brief Performs a search on a sorted range of values in O(lg n) time.
	 */
	template <std::ranges::random_access_range R, typename T>
	auto binarySearch(R&& range, T&& value) {
		const auto search = [&](auto self, auto&& subrange) {
			if(std::ranges::empty(subrange)) {
				return range.end();
			}

			// calculate the midpoint
			auto mid = subrange.begin() + std::ranges::distance(subrange) / 2;
			if(*mid == value) {
				return mid;
			}

			if(*mid > value) {
				return self(self, std::ranges::subrange(subrange.begin(), mid));
			} else {
				return self(self, std::ranges::subrange(mid + 1, subrange.end()));
			}
		};
		return search(search, std::forward<R>(range));
	}

}

#endif
