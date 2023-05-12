#ifndef DSA_SORT_HEADER
#define DSA_SORT_HEADER

#include <concepts>
#include <algorithm>
#include <ranges>
#include <vector>

/**
 * @brief Sorts a range of values in O(n^2) time.
 */
template <std::ranges::random_access_range R>
	requires std::sortable<std::ranges::iterator_t<R>>
void bubbleSort(R&& range) {
	bool sorted = false;
	for(auto it1 = range.end(); it1 != range.begin() && !sorted; it1--) {
		sorted = true;
		for(auto it2 = range.begin(); it2 != it1 - 1; it2++) {
			if(*(it2 + 1) < *it2) {
				std::iter_swap(it2 + 1, it2);
				sorted = false;
			}
		}
	}
}



/**
 * @brief Sorts a range of values in O(n^2) time.
 */
template <std::ranges::random_access_range R>
	requires std::sortable<std::ranges::iterator_t<R>>
void selectionSort(R&& range) {
	for(auto it = range.begin(); it != range.end(); it++) {
		std::iter_swap(it,
			std::min_element(it, range.end())
		);
	}
}



/**
 * @brief Sorts a range of values in O(n^2) time.
 */
template <std::ranges::random_access_range R>
	requires std::sortable<std::ranges::iterator_t<R>>
void insertionSort(R&& range) {
	for(auto it = range.begin(); it != range.end(); it++) {
		auto key = std::move(*it);
		const auto insertKey = [&]() {
			auto insertPos = it;
			while(insertPos != range.begin() && *(insertPos - 1) > key) {
				*insertPos = std::move(*(insertPos - 1));
				insertPos--;
			}
			*insertPos = std::move(key);
		};
		insertKey();
	}
}



/**
 * @brief Sorts a range of values in O(n * lg n) time.
 */
template <std::ranges::random_access_range R>
	requires std::sortable<std::ranges::iterator_t<R>>
void mergeSort(R&& range) {
	const auto merge = [&](auto left, auto right) {
		// allocate temporary storage for the result
		std::vector<std::ranges::range_value_t<decltype(left)>> result;
		result.reserve(std::ranges::distance(left) + std::ranges::distance(right));

		// iterate over the two ranges, saving the smallest element
		while(!std::ranges::empty(left) && !std::ranges::empty(right)) {
			if(left.front() < right.front()) {
				result.emplace_back(std::move(left.front()));
				left.advance(1);
			} else {
				result.emplace_back(std::move(right.front()));
				right.advance(1);
			}
		}

		// append remaining elements to the result
		std::ranges::move(left, std::back_inserter(result));
		std::ranges::move(right, std::back_inserter(result));

		// move the sorted elements back to the original sequence
		std::ranges::move(result, range.begin());
	};

	// if the range contains only one element or no elements at all, there is nothing to sort
	if(std::ranges::size(range) <= 1) {
		return;
	}
	
	// find the midpoint of the range
	const auto mid = range.begin() + std::ranges::distance(range) / 2;

	// split the range into two halves and sort them independently
	const auto left = std::ranges::subrange(range.begin(), mid);
	mergeSort(left);

	const auto right = std::ranges::subrange(mid, range.end());
	mergeSort(right);

	merge(left, right);
}

#endif
